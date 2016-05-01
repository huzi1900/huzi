#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int sockfd;
	int len;
	struct sockaddr_in address;
	int result;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("127.0.0.1");
	address.sin_port=htons(9734);
	len=sizeof(address);
	result=connect(sockfd,(struct sockaddr *)&address,len);
	if(result == -1){
		perror("oops:client");
		exit(1);
	}
	char c ='A';
	if(write(sockfd,&c,1)==1){
		printf("send c to server\n");
	}
	
	
	char rc[21];
	int r=read(sockfd,&rc,21);
	rc[r]='\0';
	printf("%s",rc);
	
	if (read(sockfd,&c,1)==1){
		printf("%c",c);
	}
	printf("\n");
	close(sockfd);
	exit(0);
}
