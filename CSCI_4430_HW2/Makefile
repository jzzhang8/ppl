CC = gcc
LIB = -lisal

all: server client

server: myftpserver.c
	${CC} -o myftpserver myftpserver.c myftp.c ${LIB} -pthread

client: myftpclient.c
	${CC} -o myftpclient myftpclient.c myftp.c ${LIB} -pthread

clean:
	rm server
	rm client	
