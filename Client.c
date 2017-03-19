/*****************************/
/*Titel: Assignment4_Client.c*/
/*   Author: Khanjan Desai   */
/*   Date  : Feb 11, 2016    */
/* Client program to execute */
/*Client-Server using Socket */
/*****************************/






#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <errno.h>


int sockfd = 0, n,i;
    

void handler(int signo)
{
    	if(signo = SIGINT)
    	{
		printf("Shut down");
		int ret = close(sockfd);
		sleep(1);
		if(ret == -1)	
		{	
			printf("Closing Error");
		}
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	// Read IP and port
    	char * ip = argv[1];
    	int ip1 = atoi(argv[2]);	
    	struct sockaddr_in serv_addr; 
    	
    	char arr[100];
	// Signal Handler
    	if(signal(SIGINT,handler) == SIG_ERR)
    	{
		printf("Cant recieve signal");
    	}    

    	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        // Error check for sockfd
    	if (sockfd==-1)
	{
		printf("sockfd error");
	}
    	memset(&serv_addr, '0', sizeof(serv_addr)); 

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = inet_addr(ip);	// Give IP
    	serv_addr.sin_port = htons(ip1); 		// Give Port


     
    	int con = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	//Error check for Connect    
    	if( (con < 0) )
    	{	
       		perror("Error in connect call ");
       		return 1;
    	}
	// Send in Infinit loop
	// If fail to send twice the client stops considering server down    
    	while(1)
    	{	
		scanf("%s",arr);	
 		int ret=   send(sockfd,arr,100,0);
		if(ret==-1)
		{
			printf("send error");
			close(con);	
    		}
    	}
    	return 0;
}
