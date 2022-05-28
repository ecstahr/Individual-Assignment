#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;
	char *message, server_reply[2000];

	//Creating socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf ("Couldn't create socket");
	}

	server.sin_addr.s_addr = inet_addr("192.168.56.110");
	server.sin_family = AF_INET;
	server.sin_port = htons ( 22 );

	//Connecting to remote serever
	if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("Connection error");
		return 1;
	}
	puts("\nConnected!\n");

	//Sending datas
	message = "Connected..\n.";
	if(send(socket_desc, message, strlen(message), 0)< 0)
	{
		puts("SEND FAILED");
		return 1;
	}
	puts("DATA SENT\n");

	//Reply from server
	if(recv(socket_desc, server_reply, 2000, 0)<0)
	{
		puts("recv failed");
	}
	puts("Reply received!\n");
	puts(server_reply);

	return 0;
}
