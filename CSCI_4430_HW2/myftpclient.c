#include "myftp.h"

#include <unistd.h>

unsigned char buff[MAXLEN];


struct server_s{
    char addr[16];
    unsigned int port;
};


int main(int argc, char **argv){
    // int port = atoi(argv[2]);
    


    N = 2;
    K = 1;
    blockSize = 1024;

    // int sd = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in server_addr;
    // memset(&server_addr, 0, sizeof(server_addr));
    // server_addr.sin_family = AF_INET;
    // server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    // server_addr.sin_port = htons(port);
    // socklen_t addrlen = sizeof(server_addr);
    // if(connect(sd,(struct sockaddr *)&server_addr, sizeof(server_addr))<0){
    //     printf("connect error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //     exit(0);
    // }

    /*  added for several socks*/
    int i;
    int sds[N];


    struct server_s servers[N];
    // below code for test only
    servers[0].port = 12345;
    servers[1].port = 12346;

    memset(servers[0].addr,0,16);
    memset(servers[1].addr,0,16);

    strcpy(servers[0].addr,"127.0.0.1");
    strcpy(servers[1].addr,"127.0.0.1");


    struct sockaddr_in server_addrs[N];
    for(i = 0; i < N; i++){
        sds[i] = socket(AF_INET, SOCK_STREAM, 0);

        memset(&server_addrs[i], 0, sizeof(struct sockaddr_in));
        server_addrs[i].sin_family = AF_INET;
        server_addrs[i].sin_addr.s_addr = inet_addr(servers[i].addr);
        server_addrs[i].sin_port = htons(servers[i].port);
    }

    for(i = 0; i < N; i++){
        if(connect(sds[i],(struct sockaddr *)&server_addrs[i], sizeof(struct sockaddr_in)) < 0){
            printf("connect error: %s (ERRNO:%d) for server: %s:%d\n",
                strerror(errno), errno,servers[i].addr,servers[i].port);
            exit(0);
        }else{
            printf("Connect to server: %s:%d\n", servers[i].addr,servers[i].port);
        }
    }


    



    unsigned char *message;
    struct message_s headerMsg;
    int sendNum;
    int recvNum;

    /*****************************
     * 
     * "list" command
     * 
     * ***************************/
    // if(strcmp("list", argv[3]) == 0){
    //     /****** send header(0XA1) *******/
    //     headerMsg.length = htonl(10);
    //     strcpy(headerMsg.protocol, "myftp");
    //     headerMsg.type = (unsigned char)0xA1;
    //     message = (unsigned char *)malloc(10);
    //     memcpy(message, &headerMsg, 10);

    //     if((sendNum = (sendn(sd, message, 10))<0)){
    //         printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //     }
    //     /****** receive header(0XA2) *******/
    //     if((recvNum = recvn(sd, buff, 10)) < 0){
    //         printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //         exit(0);
    //     }
    //     memcpy(&headerMsg, buff, 10);
    //     // headerMsg.length - 10 is the length for buff (dir info)
    //     if((recvNum = recvn(sd, buff, headerMsg.length - 10)) < 0){
    //         printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //         exit(0);
    //     }
    //     if(headerMsg.type == (unsigned char)0xA2){
    //         printf("%s", buff);
    //     }
        
    // }
    // /*****************************
    //  * 
    //  * "get" command
    //  * 
    //  * ***************************/
    // else if(strcmp("get", argv[3]) == 0){
    //     /****** send header(0XB1) *******/
    //     strcpy(headerMsg.protocol, "myftp");
    //     headerMsg.type = (unsigned char) 0xB1;
    //     // get the length of file name
    //     unsigned int fileNameLen = strlen(argv[4]);
    //     // messageLen = fileNameLen + 10(header) + 1(\0)
    //     unsigned int messageLen = fileNameLen + 11;
    //     headerMsg.length = htonl(10 + fileNameLen + 1);
    //     message = (unsigned char *)malloc(messageLen);
    //     // message  = [headerMsg, fileNameLen, '\0]
    //     memcpy(message, &headerMsg, 10);
    //     memcpy(message + 10, argv[4], fileNameLen);
    //     message[messageLen - 1] = '\0';

    //     if((sendNum = (sendn(sd, message, messageLen))<0)){
    //         printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //         exit(0);
    //     }
    //     /****** send header(0XB2/0XB3) *******/
    //     if((recvNum = recvn(sd, buff, 10)) < 0){
    //         printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //         exit(0);
    //     }

    //     memcpy(&headerMsg, buff, 10);
    //     if(headerMsg.type == 0xB3){
    //         // file not exit
    //         printf("file not exit\n");
    //         exit(0);
    //     }else if(headerMsg.type == 0xB2){
    //         /****** send header(0XFF) *******/
    //         // get file header -> get file size
    //         if((recvNum = recvn(sd, buff, 10)) < 0){
    //             printf("recv error: %s (ERRNO:%d)\n",strerror(errno), errno);
    //             exit(0);
    //         }
    //         memcpy(&headerMsg, buff, 10);
    //         FILE *fd = fopen(argv[4], "wb");
    //         // fileSize get
    //         int fileSize = ntohl(headerMsg.length) - 10;
    //         int remainSize = fileSize;
    //         int nextSize;
    //         // send message in packet(len<=MAXLEN)
    //         while(remainSize>0){
    //             nextSize = min(remainSize, MAXLEN);
    //             if((recvNum = recvn(sd, buff, nextSize)) < 0){
    //                 exit(0);
    //             }
                
    //             fwrite(buff, 1, nextSize, fd);
    //             remainSize -= nextSize;
    //         }
    //         fclose(fd);
    //     }
    // /*****************************
    //  * 
    //  * "put" command
    //  * 
    //  * ***************************/
    // }else 
    if (strcmp("put", argv[2]) == 0){
        // may need to change the index for the argv[]
        if(access(argv[3], F_OK) != 0){
            printf("file doesn't exit\n");
            exit(0);
        }

        /****** send header(0XC1) *******/
        strcpy(headerMsg.protocol, "myftp");
        headerMsg.type = (unsigned char)0xC1;
        int fileNameSize = strlen(argv[3]);
        // messageLen = headerLen(11) + fileNameSize + '\0'(1)
        unsigned int messageLen = 11 + fileNameSize + 1;
        headerMsg.length = htonl(messageLen);
        // message = [header, fileName, '\0']
        message = (unsigned char *)malloc(11+fileNameSize+1);
        memcpy(message, &headerMsg, 11);
        memcpy(message + 11, argv[3], strlen(argv[3]));
        message[messageLen - 1] = '\0';
        
        char request_send[N]; 
        /* status for the fd: 
        0 for not sent yet
        1 for request sent, reply not received yet
        2 for reply received
        */
        memset(request_send, 0, N);

        fd_set request_fd;
        fd_set reply_fd;

        int max_fd = 0;
        for(i = 0; i < N; i++){
            if(max_fd < sds[i]){
                max_fd = sds[i];
            }
        }

        int reply_received = 0;
        while(reply_received < N){
            FD_ZERO(&request_fd);
            FD_ZERO(&reply_fd);
            printf("One request or reply with reply receive: %d\n",reply_received);
            int j;
            for(j = 0; j < N; j++){
                if(request_send[j] == 0){
                    FD_SET(sds[j], &request_fd);
                }
                if(request_send[j] == 1){
                    FD_SET(sds[j], &reply_fd);
                }
            }

            int ret = select(max_fd+1, &reply_fd, &request_fd, NULL, NULL);// no timeout
            if(ret < 0){
                printf("Request and reply select error,ret: %d\n", ret);
            }

            for(j = 0; j < N; j++){
                // can send request
                if(FD_ISSET(sds[j], &request_fd)){ 
                    if((sendNum = (sendn(sds[j], message, messageLen)) < 0)){
                        printf("send error: %s (ERRNO:%d) for server: %s:%d\n",
                            strerror(errno), errno,servers[j].addr,servers[j].port);
                        exit(0);
                     }

                     printf("server %d send request\n",j);
                     request_send[j] = 1;
                     break;
                }
                // already send request, can recv reply
                if(FD_ISSET(sds[j], &reply_fd)){
                    if((recvNum = recvn(sds[j], buff, 11)) < 0){
                        printf("send error: %s (ERRNO:%d) for server: %s:%d\n",
                            strerror(errno), errno,servers[j].addr,servers[j].port);
                        exit(0);
                    }
                    memcpy(&headerMsg, buff, 11);

                    printf("server %d receive reply\n",j);
                    if(headerMsg.type != (unsigned char)0xC2){
                        printf("Reply header error, server: %s:%d\n", 
                            servers[j].addr,servers[j].port);
                        exit(0);
                    }
                    request_send[j] = 2;
                    reply_received++;
                    break;
                }
            }
        }


        //get file size 
        struct stat statbuff;
        int readFileInfoflag;
        if((readFileInfoflag = stat(argv[3], &statbuff))<0){
            printf("error read file info.");
            exit(0);
        }
        int file_size = statbuff.st_size;

        // stripe_num = ceiling( filesize / (K * blockSize) )
        int stripe_num = (file_size % (K * blockSize) == 0) ? file_size / (K * blockSize) : file_size / (K * blockSize)+1;
        FILE *fd = fopen(argv[3], "rb");
        char * cacheName = malloc(strlen(argv[3]) + 2);
        cacheName[0] = '.';
        memcpy(cacheName+1, argv[3],strlen(argv[3]));
        cacheName[strlen(argv[3])+1] = '\0';

        FILE *cachefd = fopen(cacheName,"wb");

        uint8_t *encode_matrix = malloc(sizeof(uint8_t) * N * K);
        uint8_t *errors_matrix = malloc(sizeof(uint8_t) * K * K);
        uint8_t *invert_matrix = malloc(sizeof(uint8_t) * K * K);
        uint8_t *table = malloc( sizeof(uint8_t) * 32 * K * (N - K) );

        uint8_t **blocksData = (uint8_t**)malloc(sizeof(uint8_t**) * N); 
        // ptr arrays for the blocks

        gf_gen_rs_matrix(encode_matrix, N, K);
        ec_init_tables(K, N - K, &encode_matrix[K*K], table);

        int block_idx;
        // alloc the data blocks for a stripe
        for(block_idx = 0; block_idx < N; block_idx++){
            blocksData[block_idx] = (uint8_t*)malloc(blockSize * sizeof(uint8_t));
        }

        int stripe_idx;
        int read_size = 0;
        /* ******** 
        for each file, we only generate the encode matrix and the table once 
        and use the matrix and table to encode all the stripes ******* */
        for(stripe_idx = 0; stripe_idx < stripe_num; stripe_idx++){

            for(block_idx = 0; block_idx < K; block_idx++){
                memset(blocksData[block_idx], 0, blockSize);
            }
            
            for(block_idx = 0; block_idx < K; block_idx++){
                int next_read_size = 0;
                if(file_size - read_size == 0){ // all the file get read
                    break;
                }else if(file_size - read_size < blockSize){ // rest within one block
                    next_read_size = file_size - read_size;
                }else{ // rest more than one block
                    next_read_size = blockSize;
                }

                if((fread(blocksData[block_idx], 1, next_read_size, fd)) < 0){
                    printf("File read error\n");
                    exit(0);
                }
                read_size += next_read_size;
            }
            
            ec_encode_data(blockSize, K, N-K, table, blocksData, &blocksData[K]);
            // write the cache file to ".<filename>""
            for(block_idx = 0; block_idx < N; block_idx++){
                if((fwrite(blocksData[block_idx], 1, blockSize, cachefd)) < 0){
                    printf("File write error\n");
                    exit(0);
                }
            }
        }

        fclose(cachefd);


        // read the cache which will be sent to servers
        // read the cache here

        if(access(cacheName, F_OK) != 0){
            printf("Cache file doesn't exit\n");
            exit(0);
        }
        if((readFileInfoflag = stat(cacheName, &statbuff))<0){
            printf("error read cache file info.");
            exit(0);
        }
        int cache_size = statbuff.st_size;
        cachefd = fopen(cacheName, "rb");

        //use a list to store the number of blocks to be sent to servers
        int send_nums[N];
        int server_idx;
        for(server_idx = 0; server_idx < N; server_idx++){
            send_nums[server_idx] = -1;// -1 means the file header is not sent yet
        }


        // find the max_fd
        for(server_idx = 0; server_idx < N; server_idx++){
            if(max_fd < sds[server_idx]){
                max_fd = sds[server_idx];
            }
        }

        fd_set file_fd;
        // the buffer for one block
        unsigned char *block_buf = malloc(sizeof(unsigned char) * blockSize);
        while(1){
            int all_send_flag = 1;

            for(server_idx = 0; server_idx < N; server_idx++){
                if(send_nums[server_idx] < stripe_num){
                    all_send_flag = 0;
                }
            }
            if(all_send_flag) break; // all the packets are sent

            for(server_idx = 0; server_idx < N; server_idx++){
                printf("Server %d status: %d\n",server_idx, send_nums[server_idx]);
            }
            
            // set the fd_set
            FD_ZERO(&file_fd);
            for(server_idx = 0; server_idx < N; server_idx++){
                if(send_nums[server_idx] < stripe_num){
                    FD_SET(sds[server_idx], &file_fd);
                }
            }
            
            select(max_fd+1, NULL, &file_fd, NULL, NULL);
            for(server_idx = 0; server_idx < N; server_idx++){
                if(FD_ISSET(sds[server_idx], &file_fd)){
                    if(send_nums[server_idx] == -1){ // send the file header if -1
                        /*  set up the header */
                        strcpy(headerMsg.protocol, "myftp");
                        headerMsg.type = 0xFF;
                        messageLen = 11 + file_size;
                        headerMsg.length = htonl(messageLen);
                        headerMsg.idx = server_idx;
                        memcpy(buff, &headerMsg, 11);
                        printf("to send header for server: %d\n", server_idx);
                        if(((sendn(sds[server_idx], buff, 11))<0)){
                            printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
                            exit(0);
                        }
                        printf("Send header for server: %d\n", server_idx);
                        send_nums[server_idx] += 1;
                        break;
                    }
                    // in the case sendNums[idx] >= 0, just send the blocks from the cache file
                    // the block location is calculated as "send_num * N + server_idx" and then multiplied by blockSize
                    if((fseek(cachefd, (send_nums[server_idx] * N + server_idx) * blockSize, SEEK_SET)) < 0){
                        printf("Cache file seek error\n");
                        exit(0);
                    }
                    if((fread(block_buf, 1, blockSize, cachefd)) < 0){
                        printf("Cache file read error \n");
                        exit(0);
                    }
                    if(((sendn(sds[server_idx], block_buf, blockSize))<0)){
                        printf("Send error: %s (ERRNO:%d)\n",strerror(errno), errno);
                        exit(0);
                    }
                    send_nums[server_idx] += 1;

                    break;   
                }
            }


        }


        fclose(cachefd);

        // ------------------------------------
        /****** send header(0XFF) *******/
        
        // if((sendNum = (sendn(sd, buff, 11))<0)){
        //     printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
        //     exit(0);
        // }
        // // send file in packet(len <= MAXLEN)
        // int remainFileLen = file_size;
        // int readLen;
        // int nextSize = min(MAXLEN, remainFileLen);
        // while((readLen = fread(buff, 1, nextSize, fd))>0){
        //     if((sendNum = (sendn(sd, buff, nextSize))<0)){
        //         printf("send error: %s (ERRNO:%d)\n",strerror(errno), errno);
        //         exit(0);
        //     }
        //     remainFileLen -= nextSize;
        //     nextSize = min(MAXLEN, remainFileLen);
        // }

        //------------------------------------

        fclose(fd);

        if((remove(cacheName)) != 0){ // remove the cache file here
            printf("Remove cache error\n");
            exit(0);
        }

    }

    for( i = 0; i < N; i++){
        close(sds[i]); // close all sockets
    }

    return 0;
}
