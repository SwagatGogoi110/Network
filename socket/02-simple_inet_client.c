#include <stdio.h>	
#include <stdlib.h>	
#include <unistd.h>	
#include <netinet/in.h>
#include <arpa/inet.h>	
#include <sys/socket.h>	

int main()
{
	int my_socket;
	socklen_t socket_addr_len;

	struct sockaddr_in socket_address;

	int retval;
	char ch = 'A';

	my_socket = socket(AF_INET, SOCK_STREAM, 0);

	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	socket_address.sin_port = htons(44332);
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

