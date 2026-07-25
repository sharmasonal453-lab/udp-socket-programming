/******************************************************************************
 * File Name   : udp_server.c
 * Author      : Sonal Sharma
 * Description : UDP Echo Server
 ******************************************************************************/

#define SERVER_PORT 5000
#define BUFFER_SIZE 100

#include<sys/socket.h>
#include<stdio.h>
#include<unistd.h>
#include <netinet/in.h>
#include<string.h>
#include <arpa/inet.h>


int main()
{
	char buffer[BUFFER_SIZE];
	int sockfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_len;
	ssize_t bytes_received;
	/*Create a socket for Server and configure its family,protocol & flags if any*/
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
	printf("sockfd is %d\n",sockfd);

	if(sockfd < 0)
	{
		perror("Error : SocID Creation");
		return -1;
	}

	printf("Socket created successfully\n");

	/*Clear the memory so that when accessing it, garbage value should not come*/
	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	/*Bind the Server IP address and port with socket*/
	if (bind(sockfd,
         (struct sockaddr *)&server_addr,
         sizeof(server_addr)) < 0)
	{
    		perror("Bind failed");
    		close(sockfd);
    		return -1;
	}	
	/*Receive data from Client to Server*/
	client_len = sizeof(client_addr);
	bytes_received = recvfrom(sockfd,
                          buffer,
                          sizeof(buffer) - 1,
                          0,
                          (struct sockaddr *)&client_addr,
                          &client_len);
	if (bytes_received < 0)
	{
    perror("recvfrom failed");
    close(sockfd);
    return -1;
	}
	buffer[bytes_received] = '\0';
	printf("Client IP : %s\n",inet_ntoa(client_addr.sin_addr));
	printf("Client Port : %d\n",ntohs(client_addr.sin_port));

	/*Echo back the data received from Client to Server*/
	if (sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&client_addr,client_len) < 0)
		{
   			 perror("sendto failed");
   			 close(sockfd);
    		         return -1;
		}	  	       
	return 0;
}
