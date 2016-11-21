#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr

int main(int argc , char *argv[])
{
int socket_desc;
struct sockaddr_in server;
char message[2000] , server_reply[2000];
int port_num;
//Create socket
socket_desc = socket(AF_INET , SOCK_STREAM , 0);
if (socket_desc == -1)
{
printf("Could not create socket");
}
if(argc!=3)
	printf("usage: client.c<IPaddress><Portnumber>\n");
server.sin_addr.s_addr = inet_addr(argv[1]);
server.sin_family = AF_INET;
sscanf(argv[2],"%d",&port_num);
server.sin_port = htons( port_num );
//Connect to remote server
if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
{
puts("connect error");
return 1;
}
puts("Connected\n");
//Send some data
while(1)
{
	printf("Please enter 4 numbers:");
	scanf("%s",message);
	if(send(socket_desc,message,strlen(message),0)<0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");
	//Receive a reply from the server
if( recv(socket_desc, server_reply , 2000 , 0) < 0)
{
puts("recv failed");
}
puts("Reply received\n");
puts(server_reply);	

}


return 0;
}
