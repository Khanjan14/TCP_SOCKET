/*****************************/
/*Titel: Assignment4_Server.c*/
/*   Author: Khanjan Desai   */
/*   Date  : Feb 11, 2016    */
/*Server program to execute  */
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

int listenfd = 0, connfd = 0;
    
// Signal Handler

void handler(int signo)
{
    	if(signo = SIGINT)
    	{
		printf("Shut down");
		int ret = close(listenfd);
		sleep(1);
		if(ret == -1)	printf("Closing Error");
		exit(0);
    	}
}

int main(int argc, char *argv[])
{
	// Read IP and Port address
    	char * ip = argv[1];
    	int ip2= atoi(argv[2]);

    	struct sockaddr_in serv_addr; 
		
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
    	memset(&serv_addr, '0', sizeof(serv_addr));

    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_addr.s_addr = inet_addr(ip);
    	serv_addr.sin_port = htons(ip2);
	// Signal Handler 
    	if(signal(SIGINT,handler) == SIG_ERR)
    	{
		printf("Cant recieve signal");
    	}
	// Error handler for bind
    	if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0)
	{
    		printf("Error in binding");
	    	return 1;
	} 
	// Error Handler for listenfd
    	if(listen(listenfd, 10)<0)
    	{
    		printf("Error in listening");
    		return 1;
    	} 
	// If all correct start server
    	printf("starting server...\n");
        // Error handling for recieving Client IP
    	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    	if (connfd==-1)
	{
		perror("Error:");   
	}
	while(1)
    	{
        	char arr[100];
		// Recieve Data
		int ret=   recv(connfd,arr,100*sizeof(arr),0); 	
		// Error handler for recv with printing data	
		if (ret !=-1)
		{	
			printf("recieve:%s\n",arr);        
			send(connfd,arr,100*sizeof(arr),0);
	
		}
		// In error go to else
		else
		{
			printf("recive error\n");
              	  	//System reconnect		
			connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    			if (connfd==-1)
			{
				perror("Error:");
				exit(1);
			}   
		}	
    	}

}
