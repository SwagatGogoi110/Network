#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

int main()
{
   int client_socket;
   struct sockaddr_in server_address;
   char buffer[BUFFER_SIZE];

   client_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (client_socket == -1)
   {
      perror("Failed to create socket");
      exit(EXIT_FAILURE);
   }

   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = INADDR_ANY;
   server_address.sin_port = htons(8888);

   if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
   {
      perror("Failed to bind");
      exit(EXIT_FAILURE);
   }

   printf("Connected to server...\n");

   while (1)
   {
      printf("Enter the message (or 'q' to quit): ");
      fgets(buffer, BUFFER_SIZE, stdin);
      
      if(strcmp(buffer, "q\n") == 0)
         break;
      
      if(send(client_socket, buffer, strlen(buffer), 0) < 0){
         perror("Failed to send");
         exit(EXIT_FAILURE);
      }

      memset(buffer, 0, BUFFER_SIZE);
      if(recv(client_socket, buffer, BUFFER_SIZE, 0) < 0){
         perror("Failed to receive");
         exit(EXIT_FAILURE);
      }

      printf("Server response: %s", buffer);
   }

   close(client_socket);
   return 0;
}
