#include <stdio.h>
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>
#include <sys/un.h>	
#include <sys/socket.h>	

int main()
{
	int my_socket;
	socklen_t socket_addr_len;

	struct sockaddr_un socket_address;

	int retval;
	char ch = 'A';
	
	my_socket = socket(AF_UNIX, SOCK_STREAM, 0);

	socket_address.sun_family = AF_UNIX;
	strcpy(socket_address.sun_path, "server_socket");
	socket_addr_len = sizeof(socket_address);

	retval = connect(my_socket, (struct sockaddr *)&socket_address, socket_addr_len);

	if( retval == -1 )
	{
		perror("Client Error");
		exit(EXIT_FAILURE);
	}

	write(my_socket, &ch, 1);
	read(my_socket, &ch, 1);

	printf("Received from Server: %c\n", ch);

	close(my_socket);

	return 0;
}

