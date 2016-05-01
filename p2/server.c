#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int server_sockfd,client_sockfd;
	int server_len,client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd=socket(AF_INET,SOCK_STREAM,0);
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port=htons(9734);
	server_len=sizeof(server_address);

	bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
	listen(server_sockfd,5);
	while(1){
		char c;
		printf("server waiting\n");
		client_len=sizeof(client_address);
		client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
		read(client_sockfd,&c,1);
		printf("from client:%c\n",c );
		c++;
		char *ip =inet_ntoa(client_address.sin_addr);
		write(client_sockfd,ip,strlen(ip));
		write(client_sockfd,&c,1);
		}
	close(client_sockfd);
	exit(0);
	}


