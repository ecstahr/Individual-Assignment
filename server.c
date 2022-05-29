#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8008

int main(int argc, char const *argv[])
{
	int server_fd, new_socket; long valread;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	//HTTP protocol implementation using index.html file
	char *hello = "HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html; charset= UTF-8\r\n\r\n"
			//"Content-Type: image/jpeg;"
			"<!DOCTYPE html>\r\n"
			"<html><head><title>ANYA SUPREMACY</title></head>\r\n"
			"<body style='background colour:powderblue;'>"
			"<h1>SPY X FAMILY</h1>\r\n"
			"<body><p>Loid Forger, Anya Forger, Yor Forger</p>\r\n"
			//"<body><img src='/home/adr4/http/Anya.Forger.600.3428862.jpg' style ='width:600px; height: 529px;'/>"
			//"<body><img src='i.pinimg.com/736x/df/a9/f3/dfa9f37552c64d97dd47330509c0470e.jpg'style ='width:600px; height: 529px;'/>"
			"</body><html>\r\n" ;

	//Creating socket file descriptor
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET; //Address family used to set up socket
	address.sin_addr.s_addr = INADDR_ANY; //Address for socket
	address.sin_port = htons( PORT ); //Specify port number for client to connect

	memset(address.sin_zero, '\0', sizeof address.sin_zero);

	//Creating a file in the system file
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	//Accepting connections
	if(listen(server_fd,10) < 0)
	{
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}


	while(1)
	{
		printf("\n\nWaiting for connections....\n\n");
		//Accept grabs the first conection
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
		{
			perror("Accept failed");
			exit(EXIT_FAILURE);
		}
		//read and write variable for communication
		char buffer[30000] = {0};

		//read data from client
		valread = read(new_socket, buffer, 30000);
		printf("%s\n", buffer);

		//write to client
		write(new_socket, hello, strlen(hello));
		printf("\n Yay, Message sent!");

		//Close socket
		close(new_socket);
	}
	return 0;
}
