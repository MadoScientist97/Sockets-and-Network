#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

char* getTime(){
  char *ti=(char*)malloc(300);
  bzero(ti,100);
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  sprintf ( ti,"%s%c", asctime (timeinfo),'\n' );
  return ti;
}
int main(){
	char *intime;
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("10.0.0.2");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		printf("Client: \t");
	//	scanf("%s", &buffer[0]);
///////////////////////////////////////////////////////////////////////////////////////////////////
        bzero(buffer,1024);
        int n = 0; 
        char inp[6];
        while ((inp[n++] = getchar()) != '\n');
        sprintf(buffer,"%s\n%c",inp,'\0');
           

///////////////////////////////////////////////////////////////////////////////////////////////////
		send(clientSocket, buffer, strlen(buffer), 0);

		if(buffer[0] == 'e'){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		if(recv(clientSocket, buffer, 1024, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			intime=getTime();
			printf("Server Reply: \t%sRecieved at Client time: %s:", buffer,intime);
		}
	}

	return 0;
}