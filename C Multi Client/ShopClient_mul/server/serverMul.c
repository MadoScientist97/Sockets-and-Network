#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 80 
#define PORT 4444

sem_t Ma; 
sem_t Ap; 
sem_t Ki; 
sem_t Ba; 
int fruits[4]={50,50,50,50};

char* getTime(){
  char *ti=(char*)malloc(25);
  bzero(ti,25);
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  sprintf ( ti,"%s%c", asctime (timeinfo),'\0' );
  return ti;
}
void w2file(void){ 
    FILE *filePointer ;
    filePointer = fopen("DB.txt", "w") ;
    for (int i=0;i<4;i++){ 
        fprintf(filePointer,"%d",fruits[i]) ;    
        fprintf(filePointer," ") ;
    }
  fclose(filePointer) ;  
}
void read4file( ) 
{  
 FILE* file = fopen ("DB.txt", "r");
  int i = 0;
  fscanf (file, "%d", &i);    
  for (int p=0;p<4;p++)
    { 
      fruits[p]=i;
      fscanf (file, "%d", &i);      
    }
  fclose (file);        
}


int main(){
	w2file();
	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;

	sem_init(&Ma, 0, 1);
	sem_init(&Ap, 0, 1);
	sem_init(&Ki, 0, 1);
	sem_init(&Ba, 0, 1);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("10.0.0.2");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}

	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
		char *Intime;
		Intime=getTime();
		printf("At Server Time: %s",Intime);
		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				recv(newSocket, buffer, 1024, 0);
				if(buffer[0] == 'e'){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					close(newSocket);
          break;
				}
				else{
				  printf("\nClient IP-%s:port-%d",inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    if (buffer[0] == 'm' || buffer[0] == 'M')
                    {    
                        printf(" Ordered: %c %c",buffer[0],buffer[2]);
						Intime=getTime();
						printf("\nAt Server Time: %s",Intime);
                	    sem_wait(&Ma);
                	    read4file();
                	    if (fruits[0]!=0){
                	    fruits[0] = fruits[0] - ((int)buffer[2] -48);
                	    w2file();
                	    printf("\nMango Ordered: %d ",buffer[2]);
                        bzero(buffer, MAX);     //empty buffer
                        Intime=getTime();
                        sprintf(buffer,"Remaining Fruits are:\nMango:%d\nApple:%d\nKiwi:%d\nBanana:%d\nServer Sent Reply At %s\n%c",fruits[0],fruits[1],fruits[2],fruits[3],Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));
				   		}
				   		else
                    	{
                    	bzero(buffer, MAX);     //empty buffer
                        Intime=getTime();
                        sprintf(buffer, "\nSorry No Mango left.\nServer Sent Reply At %s\n%c",Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));	
                    	}
                    	sem_post(&Ma);
                    }
                    else if (buffer[0] == 'a' || buffer[0] == 'A')
                    {	 
              		    printf(" Ordered: %c %c",buffer[0],buffer[2]);
                	    Intime=getTime();
						printf("\nAt Server Time: %s",Intime);
                	    sem_wait(&Ap);
                	    read4file();
                	    if (fruits[1]!=0){
                	    fruits[1] = fruits[1] - ((int)buffer[2] -48);
                	    w2file();
                	    printf("\nApple: %d ",buffer[2]);
                        bzero(buffer, MAX);     //empty buffer
                        Intime=getTime();
                        sprintf(buffer,"Remaining Fruits are:\nMango:%d\nApple:%d\nKiwi:%d\nBanana:%d\nServer Sent Reply At %s\n%c",fruits[0],fruits[1],fruits[2],fruits[3],Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));
                    	}
                    	else
                    	{
                    	bzero(buffer, MAX);     //empty buffer
                        Intime=getTime();
                        sprintf(buffer, "\nSorry No Apple left.\nServer Sent Reply At %s\n%c",Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));	
                    	}
                    	sem_post(&Ap);
                    }

                    else if (buffer[0] == 'k' || buffer[0] == 'K')
                    {	
              		    printf(" Ordered: %c %c",buffer[0],buffer[2]);
                		Intime=getTime();
						printf("\nAt Server Time: %s",Intime);
                	    sem_wait(&Ki);
                		read4file();
                		if (fruits[2]!=0){
                		fruits[2] = fruits[2] - ((int)buffer[2] -48);
                		w2file();
                		printf("\nKiwi Ordered :%d ",buffer[2]);
                   		bzero(buffer, MAX);     //empty buffer
				   		Intime=getTime();
                        sprintf(buffer,"Remaining Fruits are:\nMango:%d\nApple:%d\nKiwi:%d\nBanana:%d\nServer Sent Reply At %s\n%c",fruits[0],fruits[1],fruits[2],fruits[3],Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));
                      	}
                      	else
                    	{
                    	bzero(buffer, MAX);     //empty buffer
                        Intime=getTime();
                        sprintf(buffer, "\nSorry No Kiwi left.\nServer Sent Reply At %s\n%c",Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));	
                    	}
                    	sem_post(&Ki);
                    }
                    else if (buffer[0] == 'b' || buffer[0] == 'B')
                    {

              		    printf(" Ordered: %c %c",buffer[0],buffer[2]);
                    	Intime=getTime();
						printf("\nAt Server Time: %s",Intime);
                	    sem_wait(&Ba);
                    	read4file();
                		if (fruits[3]!=0){
                		fruits[3] = fruits[3] - ((int)buffer[2] -48);
                		w2file();
                		printf("\nBanana Ordered: %d ",buffer[2]);
                   		bzero(buffer, MAX);     //empty buffer
				   		Intime=getTime();
                        sprintf(buffer,"Remaining Fruits are:\nMango:%d\nApple:%d\nKiwi:%d\nBanana:%d\nServer Sent Reply At %s\n%c",fruits[0],fruits[1],fruits[2],fruits[3],Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));
                    	}
                    	else
                    	{
                    	bzero(buffer, MAX);     //empty buffer
                    	Intime=getTime();
                        sprintf(buffer, "\nSorry No Banana left.\nServer Sent Reply At %s\n%c",Intime,'\0');
				   		send(newSocket, buffer, strlen(buffer)+1, 0);
				   		bzero(buffer, sizeof(buffer));	
                    	}
                    	sem_post(&Ba);
                    }

                }
			}
		}
	}
  sem_destroy(&Ma);
  sem_destroy(&Ap); 
  sem_destroy(&Ki); 
  sem_destroy(&Ba);  
  close(newSocket);
return 0;
}
