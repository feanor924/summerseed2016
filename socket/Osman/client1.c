//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
//for struct sockaddr_in and socket parameters

#ifndef DEBUG
#define DEBUG 0
#endif
/*----------------------------------------*/
int discovery(){}

int listen_hello_request(){}

int listen_hello_response(){}

int send_message(){}

int receive_message(){}
/*----------------------------------------*/

int main(int argc, char const *argv[])
{
	int listendfd=0,connfd=0;
	struct sockaddr_in server_addr;
	char recMessage[1024];
	int option = 1 ;
	char  sendMessage[1024] ;
	char temp[20],*temp2;
  	/*------create socket --------*/
	listendfd = socket(AF_INET,SOCK_STREAM,0);
	if(listendfd<0)
		perror("dont create socket\n");
	else
		printf("Socket create succes\n");

	/*------assign socket for timeout------*/
	setsockopt(listendfd,SOL_SOCKET,SO_REUSEADDR,
       &option, sizeof(option));
	
	//set server address initiliaze '0'
	memset(&server_addr,'0',sizeof(server_addr));
	
	/*------------server address  set ------*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10000);
	
	if (DEBUG){
		printf("bind..\n");
	}
	
	//Server address bind socket
	bind(listendfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	if (DEBUG){
		printf("end bind\n");
	}

	//listen socket
	if (listen(listendfd,10)==-1)
	{
		printf("failed listen\n");
		return -1;
	}

	
	while(1){
		
		printf("-----------------START------------------\n");
		printf("waiting for accept request...\n");
		
		//if come a request to socket ,accept
		if((connfd = accept(listendfd,(struct sockaddr *)NULL,NULL))<0){
	      perror("Accept Failed \n");
	  	}else{
			printf("\nAccept request\n");
		}

		//read message the socket
		read(connfd,&recMessage,1024);
		strcpy(temp,strtok(recMessage,","));
		printf("Ip address : %s\n",temp );
		while(temp2=strtok(NULL,",")){
			printf("Nick : %s\n",temp2);
		}
		
		/*-----close connection-----*/
		close(connfd);

		printf("Terminated connection\n");
		printf("-----------------END------------------\n\n");
		 
	}

	return 0;
}