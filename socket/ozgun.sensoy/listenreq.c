#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_PACKET_LENGTH 512

extern int listener(int port);

int main(){
	while(1){
		listener(10000);
	}
}
