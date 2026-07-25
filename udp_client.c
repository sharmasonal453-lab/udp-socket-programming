/******************************************************************************
 * File Name   : udp_client.c
 * Author      : Sonal Sharma
 * Description : UDP Echo Server
 ******************************************************************************/

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
	socklen_t server_len;
	ssize_t bytes_send;
	char buffer_recv[100];
	ssize_t bytes_received;
	/*Create a socket for Client and configure its family,protocol & flags if any*/
	sockfd = socket(PF_INET,SOCK_DGRAM,0);
	printf("sockfd is %d\n",sockfd);

	if(sockfd < 0)
	{
		perror("Error : SocID Creation");
		return -1;
	}

	printf("Socket created successfully\n");
	/*Clear the memory  so that when accessing it, garbage value should not come*/
	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	inet_pton(AF_INET,"127.0.0.1",&server_addr.sin_addr);	

	printf("Client wants to send data.Waiting for user to enter data...\n");
	fgets(buffer, sizeof(buffer), stdin);
	/*Sending data from Client to Server*/
	if (sendto(sockfd,
           buffer,
           strlen(buffer),
           0,
           (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0)
           {		
    		perror("sendto failed");
    		close(sockfd);
    		return -1;
		}
	printf("Message sent successfully\n");  
	server_len = sizeof(server_addr);	
	/*Receive data from Server to Client*/
	bytes_received = recvfrom(sockfd,
                          buffer_recv,
                          sizeof(buffer_recv) - 1,
                          0,
                          (struct sockaddr *)&server_addr,
                          &server_len);
	if (bytes_received < 0)
	{
    perror("recvfrom failed");
    close(sockfd);
    return -1;
	}
	buffer[bytes_received] = '\0';
	printf("Message received from server : %s\n",buffer_recv);
	printf("Server IP : %s\n",inet_ntoa(server_addr.sin_addr));
	printf("Server Port : %d\n",ntohs(server_addr.sin_port));   
	return 0;
}
