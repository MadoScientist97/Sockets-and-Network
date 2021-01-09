#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> //for close
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>


//Function to get the local time in string form
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
  int clientSocket;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t addr_size;
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);//new socket created for client to connect, the parameters are domain (v4 or v6),type(tcp/udp),protocol(IP?)
  /*---- Configure settings of the server address struct ----*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(50000);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  /* Set all bits of the padding field to 0 */
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  /*---- Connect the socket to the server using the address struct ----*/
  connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  /* ----  Send something to server ---- */
  char *ti=getTime();
  bzero(buffer,1024);
  sprintf(buffer, "\nHey server, this is me, client. \nAnd The current Client local time is: %s%c",ti,'\0');
  send(clientSocket,buffer, strlen(buffer), 0);
  /*---- Read the message from the server into the buffer ----*/
  recv(clientSocket, buffer, 1024, 0);
  /*---- Print the received message ----*/
  printf("\nData received from server: %s",buffer);   
  return 0;
}

