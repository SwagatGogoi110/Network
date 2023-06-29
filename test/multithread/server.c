#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 1024

void *client_handler(void *arg){
   int client_socket = *(int *) arg;
   char buffer[BUFFER_SIZE];
   int received_bytes;

   while ((received_bytes = recv(client_socket, buffer, BUFFER_SIZE,0)))
   {
      printf("Received: %s", buffer);
      if (send(client_socket, buffer, received_bytes,0) < 0)
      {
         perror("Failed to send");
         exit(EXIT_FAILURE);
      }
      memset(buffer, 0, BUFFER_SIZE);
   }

   if (received_bytes == 0)
   {
      printf("Client Disconnected\n");
      close(client_socket);
   }
   else if (received_bytes == -1)
   {
      perror("Failed to receive");
      exit(EXIT_FAILURE);
   }

   pthread_detach(pthread_self());
   pthread_exit(NULL);
}

int main(){
   int server_socket, client_socket;
   struct sockaddr_in server_address, client_address;
   pthread_t tid;
   int client_count = 0;

   server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket == -1)
   {
      perror("Failed to create socket");
      exit(EXIT_FAILURE);
   }

   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = INADDR_ANY;
   server_address.sin_port = htons(8888);

   if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
   {
      perror("Failed to bind");
      exit(EXIT_FAILURE);
   }

   if (listen(server_socket, MAX_CLIENTS) < 0)
   {
      perror("Failed to listen");
      exit(EXIT_FAILURE);
   }

   printf("Server listening on port 8888...\n");

   while (1)
   {
      socklen_t client_address_len = sizeof(client_address);
      client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
      if (client_socket < 0)
      {
         perror("Failed to accept");
         exit(EXIT_FAILURE);
      }
      printf("New client connected\n");
      if(pthread_create(&tid, NULL, client_handler, (void *)&client_socket) != 0){
         perror("Failed to create thread");
         exit(EXIT_FAILURE);
      }
      client_count++;
      printf("Total client connected: %d\n", client_count);
   }
   return 0;
}
