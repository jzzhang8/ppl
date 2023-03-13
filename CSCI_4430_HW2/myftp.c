#include "myftp.h"
int sendn(int sd, void *buf, int buf_len)
{

    int n_left = buf_len;
    int n;
    while(n_left > 0){
        if((n = send(sd, buf+(buf_len-n_left), n_left, 0))<0){
            if(errno == EINTR){
                n = 0;
            }else{
                return -1;
            }
        }else if(n == 0){
            return 0;
        }
        n_left -= n;
    }
    return buf_len;
}
int recvn(int sd, void *buf, int buf_len){
    int n_left = buf_len;
    int n;
    while(n_left > 0){
        if((n = recv(sd, buf+(buf_len - n_left), n_left, 0))<0){
            if(errno == EINTR)
                n = 0;
            else
                return -1;
        }else if(n  == 0){
            return 0;
        }
        n_left -= n;
    }
    return buf_len;
}



void *threadFun(void *arg){
    // handle arg
    unsigned char buff[MAXLEN];
    struct _threadParam threadParam;
    memcpy(&threadParam, (struct _threadParam *)arg, sizeof(threadParam));
    int client_sd = threadParam.client_sd;
    int n;
    if((n = recvn(client_sd, buff, 11)) < 0){
        printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
        exit(0);
    }
    buff[n] = '\0';
    int i;

    struct message_s header_msg;
    memcpy(&header_msg, buff, 11);
    int sendNum, recvNum;
    
    if(header_msg.type == (unsigned char)0xA1){
        DIR *dir;
        struct dirent *ptr_dir;
        dir = opendir("data/");
        int fileListSize = 1;
        while((ptr_dir = readdir(dir))!=NULL){
            fileListSize += strlen(ptr_dir->d_name);
            fileListSize += 1;
        }
        closedir(dir);
        char *fileList = (char *)malloc(fileListSize);
        dir = opendir("data/");
        int fileListStrPtr = 0;
        while((ptr_dir = readdir(dir))!=NULL){
            memcpy(fileList + fileListStrPtr, ptr_dir->d_name, strlen(ptr_dir->d_name));
            fileListStrPtr += strlen(ptr_dir->d_name);
            fileList[fileListStrPtr] = '\n';
            fileListStrPtr ++;
        }
        fileList[fileListSize - 1] = '\0';
        struct message_s header_msg_response;
        strcpy(header_msg_response.protocol, "myftp");
        header_msg_response.type = (unsigned char)0xA2;
        unsigned int len_header_msg_response = 10+strlen(fileList)+1;
        header_msg_response.length = htonl(len_header_msg_response);
        unsigned char *sendString = (unsigned char *)malloc(len_header_msg_response);
        memcpy(sendString, &header_msg_response, 10);
        memcpy(sendString+10, fileList, strlen(fileList));
        sendString[len_header_msg_response - 1] = '\0';
        if((sendNum = (sendn(client_sd, sendString, len_header_msg_response))<0)){
            printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
        }
        
    }else if(header_msg.type == (unsigned char)0xB1){

        int fileNameSize = ntohl(header_msg.length) - 10;
        unsigned char *sendFileName = (unsigned char *)malloc(fileNameSize);

        if((n = recvn(client_sd, buff, fileNameSize)) < 0){
            printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
            exit(0);
        }
        memcpy(sendFileName, buff, fileNameSize);
        char *sendFileDir = (char *)malloc(fileNameSize + 5+1);
        strcpy(sendFileDir, "data/");
        strcpy(sendFileDir+5, sendFileName);
        sendFileDir[fileNameSize+6] = '\0';
        int flagExitFile = 0;
        if(access(sendFileDir, F_OK) != 0){
            flagExitFile = 0;
        }else{
            flagExitFile = 1;
        }
    
        struct message_s header_msg_response;
        strcpy(header_msg_response.protocol, "myftp");
        header_msg_response.length = htonl(10);
        
        if(flagExitFile){
            header_msg_response.type = (unsigned char)0xB2;
        }else{
            header_msg_response.type = (unsigned char)0xB3;
        }
        unsigned char *sendString = (unsigned char *)malloc(10);
        memcpy(sendString, &header_msg_response, 10);
        if((sendNum = (sendn(client_sd, sendString, 10))<0)){
            printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
        }
        if(flagExitFile){
            FILE *fd = fopen(sendFileDir, "rb");
            strcpy(header_msg.protocol, "myftp");
            header_msg.type = 0xFF;
            struct stat statbuff;
            int readFileInfoflag;
            if((readFileInfoflag = stat(sendFileDir, &statbuff))<0){
                printf("error read file info.");
                exit(0);
            }
            int file_size = statbuff.st_size;
            int len_header_msg = 10 + file_size;
            header_msg.length = htonl(len_header_msg);
            memcpy(buff, &header_msg, 10);
            int remainFileLen = file_size;
            int readLen;
            if((sendNum = sendn(client_sd, buff, 10))<0){
                printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
                exit(0);
            }
            int nextSize=  min(MAXLEN, remainFileLen);
            while((readLen = fread(buff, 1, nextSize, fd))>0){
                nextSize=  min(MAXLEN, remainFileLen);
                if((sendNum = (sendn(client_sd, buff, nextSize))<0)){
                    printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
                    exit(0);
                }
                remainFileLen -= nextSize;
            }
            fclose(fd);
        }

    }else if(header_msg.type == (unsigned char)0xC1){


        int fileNameSize = ntohl(header_msg.length) - 11;
        unsigned char *recvFileName = (unsigned char *)malloc(fileNameSize);

        struct fileInfo_s fileInfo;
        memset(fileInfo.fileName, 0, 1024); //initialize the filename
        
        
        if((n = recvn(client_sd, buff, fileNameSize)) < 0){
            printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
            exit(0);
        }
        memcpy(recvFileName, buff, fileNameSize);
        memcpy(fileInfo.fileName, buff, fileNameSize);
        // copy the filename to fileInfo

        struct message_s header_msg_response;
        strcpy(header_msg_response.protocol, "myftp");
        header_msg_response.type = (unsigned char)0xC2;
        header_msg_response.length = htonl(11);
        
        unsigned char *sendString = (unsigned char *)malloc(11);
        memcpy(sendString, &header_msg_response, 11);
        if((sendNum = (sendn(client_sd, sendString, 11))<0)){
            printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
        }
        if((recvNum = recvn(client_sd, buff, 11)) < 0){
            printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
            exit(0);
        }
        memcpy(&header_msg, buff, 11);
        if(header_msg.type == (unsigned char)0xFF){
            char *recvFileDir = (char *)malloc(fileNameSize + 5+1);
            strcpy(recvFileDir, "data/");
            strcpy(recvFileDir+5, recvFileName);
            recvFileDir[fileNameSize+6] = '\0';
            
            FILE *fd = fopen(recvFileDir, "wb");
            

            int fileSize;
            int org_file_size = ntohl(header_msg.length) - 11;
            printf("Received file: %s, size: %d\n", recvFileName, org_file_size);
            
            if(org_file_size % (K*blockSize) == 0){
                fileSize = org_file_size / K;
            }else{
                fileSize = (org_file_size + (K*blockSize - org_file_size % (K*blockSize))) / K; 
            }
            
            printf("Save size: %d\n",fileSize );
            fileInfo.fileSize = org_file_size;
            fileInfo.idx = header_msg.idx;
            memcpy(buff, &fileInfo, FILEINFOSIZE);

            if(access(".metadata",F_OK) == 0){
                // metadata exists, check file recorded in meta or not
                // -------check for override here---------

                struct stat metastat;
                if((stat(".metadata", &metastat))<0){
                    printf("error read metadata info.");
                    exit(0);
                }

                int metadata_size = metastat.st_size;
                if(metadata_size % FILEINFOSIZE != 0){
                    printf("Metadata szie error, size: %d\n", metadata_size);
                    exit(0);
                }

                int file_num = metadata_size / FILEINFOSIZE;
                FILE* meta_attempt = fopen(".metadata","rb");
                int file_idx = 0;
                int file_loc = -1;
                struct fileInfo_s fileinfo_tmp;
                for(file_idx = 0; file_idx < file_num; file_idx++){
                    if((fread(&fileinfo_tmp, 1, FILEINFOSIZE, meta_attempt)) < 0){
                        printf("File info read error for checking file already exists\n");
                        exit(0);
                    }
                    if(strcpy(fileinfo_tmp.fileName, recvFileName) == 0){
                        // file already exists
                        file_loc = file_idx;
                        break;
                    }

                }
                fclose(meta_attempt);

                // ---------------------------------------

                if(file_loc == -1){
                    // file not exists in metadata yet
                    // append the fileinfo to metadata
                    FILE *metafd = fopen(".metadata", "ab");// add the metadata fd
                    if((fwrite(buff, 1, FILEINFOSIZE, metafd)) < 0){ 
                        printf("Metadata write error for file: %s\n", fileInfo.fileName);
                    }
                    fclose(metafd);

                }else{
                    // file already exists in metadata, with loc of file_loc
                    // override the fileinfo in metadata
                    FILE* meta_override = fopen(".metadata","rb+");
                    if(fseek(meta_override, FILEINFOSIZE * file_loc,SEEK_SET) < 0){
                        printf("Metadata seek error\n");
                        exit(0);
                    }
                    if(fwrite(buff, 1, FILEINFOSIZE, meta_override) < 0){
                        printf("Metadata overwrite error\n");
                        exit(0);
                    }
                    fclose(meta_override);
                }

            }else{
                // .metadata not exists
                // write the fileinfo to metadata
                FILE *metafd = fopen(".metadata", "ab");// add the metadata fd
                if((fwrite(buff, 1, FILEINFOSIZE, metafd)) < 0){ 
                    printf("Metadata write error for file: %s\n", fileInfo.fileName);
                }
                fclose(metafd);
            }
            

            

            int remainSize = fileSize;
            int nextSize;
            while(remainSize>0){
                nextSize = min(remainSize, MAXLEN);
                if((recvNum = recvn(client_sd, buff, nextSize)) < 0){
                    printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
                    exit(0);
                }
                fwrite(buff, 1, nextSize, fd);
                remainSize -= nextSize;
            }
            fclose(fd);
        }
    }
    close(client_sd);
    int threadIdx = threadParam.threadClientIdx;
    //printf("finish idx:%d\n", threadIdx);
    fflush(stdout);
    threadClient[threadIdx].available = 1;
}
