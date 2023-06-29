#include <stdio.h>	
#include <sys/socket.h>	
#include <sys/un.h>	
#include <string.h>	
#include <unistd.h>	
#include <stdlib.h>	

int main()
{
	int server_socket, client_socket;
	socklen_t server_addr_len, client_addr_len;

	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	int retval;

	unlink("server_socket");
	server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_addr_len = sizeof(server_address);
	retval = bind(server_socket, (struct sockaddr *)&server_address, server_addr_len);

	if( retval == -1 )
	{
		perror("Bind Error");
		exit(EXIT_FAILURE);
	}
	
	listen(server_socket, 5);

	while(1)
	{
		char ch;
		printf("Server waiting...\n");

		client_addr_len = sizeof(client_address);
		client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);

		read(client_socket, &ch, 1);
		ch++;
		write(client_socket, &ch, 1);
		
		close(client_socket);
	}
}

