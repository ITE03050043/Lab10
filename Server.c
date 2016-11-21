#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include<time.h>
void *connection_handler(void *);
int main(int argc , char *argv[])
{
int socket_desc , new_socket , c , *new_sock;
struct sockaddr_in server , client;
char *message;

//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
//Prepare the sockaddr_in structure
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons( 8888 );
//Bind
if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("bind failed");
return 1;
}
puts("bind done");
//Listen
listen(socket_desc , 3);
//Accept and incoming connection
puts("Waiting for incoming connections...");
c = sizeof(struct sockaddr_in);
while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
{
puts("Connection accepted");
//Reply to the client
pthread_t sniffer_thread;
new_sock = malloc(1);
*new_sock = new_socket;
if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
{
perror("could not create thread");
return 1;
}
//Now join the thread , so that we dont terminate before the thread
//pthread_join( sniffer_thread , NULL);
puts("Handler assigned");
}
if (new_socket<0)
{
perror("accept failed");
return 1;
}
return 0;
}
void *connection_handler(void *socket_desc)
{
//Get the socket descriptor
char client_message[2000],str[4];
int read_size;
int i,p,num;
int no[10],Ans[10];
int guess[4],int_guess;
int tmp,counterA,counterB,j,k;
int sock = *(int*)socket_desc;
char *message;

///////////////////
for ( i = 0 ; i < 10 ; ++i )
no[i] = i;
srand(time(NULL)) ;
for ( i = 0 ; i < 4 ; ++i ) {
p = rand() % 10 ;
if ( p == i ) continue ;
tmp = no[i] ;
no[i] = no[p] ;
no[p] = tmp ;}
printf("%d%d%d%d\n",no[3],no[2],no[1],no[0]);
//Reply to the client
while(1)
{
bzero(str,4);
read(sock,str,4);
printf("!!!\n");
int_guess=(str[0]-'0')*1000+(str[1]-'0')*100+(str[2]-'0')*10+(str[3]-'0')*1;
guess[3] = int_guess / 1000 ;
guess[2] = ( int_guess / 100 ) % 10 ;
guess[1] = ( int_guess / 10 ) % 10 ;
guess[0] = int_guess% 10 ;
counterA = counterB = 0;
for( j = 0 ; j < 4 ; ++j )
for( k = 0 ; k < 4 ; ++k )
if( no[j] == guess[k] )
if( j == k )
counterA++;
else
counterB++;

if( counterA == 4 )
{
message="Right number!!\n";
write(sock,message,strlen(message));
return 1;
}
else
{
sprintf(client_message,"Hint: %dA%dB\n",counterA,counterB);
write(sock,client_message,strlen(client_message));
counterA=0;
counterB=0;
}
}
free(socket_desc);
return 0;
}
