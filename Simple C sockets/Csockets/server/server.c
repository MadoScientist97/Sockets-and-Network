#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> //for close
#include <sys/socket.h>
#include <string.h>
#include <time.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

//function to get the local time in string form
char* getTime(){
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  char *ti=(char*)malloc(25);
  bzero(ti,25);
  sprintf ( ti,"%s%c", asctime (timeinfo),'\0');
  return ti;
}

int main(){
  int welcomeSocket, newSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_in serverStorage;
  socklen_t addr_size;
  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0); //new socket created, the parameters are domain (v4 or v6),type(tcp/udp),protocol(IP?)
  /*---- Setting server properties (ip and port) in a sockaddr_in struct ----*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(50000);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero); //setting bits of padding field to 0  
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); //Binding the IP and port
  if(listen(welcomeSocket,5)==0) //now server will listen for incoming requests, can service a maximum of 5 simultaneous connections
    printf("Listening\n");
  else
    printf("Error\n");
 /*what to do  after accepting*/
 while(1) 
 {
  addr_size = sizeof serverStorage;
  newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
  //using another socket and another sockaddr_in to store and accept the client's address and relevant flags 
  struct sockaddr_in* cliIP = (struct sockaddr_in*)&serverStorage;
  struct in_addr ipAddr = cliIP->sin_addr;
  char str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &ipAddr, str, INET_ADDRSTRLEN);
  char* ID = cliIP->sin_zero;
  char str2[8];
  inet_ntop(AF_INET, &ID, str2, 8);
  //to display client ip and port
  printf("\nClient IP is: %s", str);
  printf("\nClient port is: %d", serverStorage.sin_port);
  int i;
  for (i=0;i<8;i++){
	printf("%c", serverStorage.sin_zero[i]);
  }
  //sending a reply
  bzero(buffer,1024);
  char* ti=getTime(); //getting current local time
  sprintf(buffer, "Welcome from server. \nAnd The current server time is:%s%c",ti,'\0');
  send(newSocket,buffer,strlen(buffer)+1,0);
  //recieve client's reply
  recv(newSocket, buffer, 1024, 0);
  printf("\nData received from client is: %s", buffer);   
  close(newSocket);
  }
  return 0;
}