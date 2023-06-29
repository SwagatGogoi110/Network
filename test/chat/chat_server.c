#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024
#define PORT 8080

int main(){
   int sockfd;
   char buffer[BUFF_SIZE];
   struct sockaddr_in server_addr, client_addr;
   socklen_t client_len = sizeof(client_addr);
   socklen_t server_len = sizeof(server_addr);

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      perror("Socket creation failed");
      exit(EXIT_FAILURE);
   }

   memset(&server_addr, 0, sizeof(server_addr));
   memset(&client_addr, 0, sizeof(client_addr));

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(PORT);

   if(bind(sockfd, (const struct sockaddr*)&server_addr, server_len) <0){
      perror("Bind Failed");
      exit(EXIT_FAILURE);
   }

   if (listen(sockfd,5) < 0)
   {
      perror("Error in listening");
      exit(EXIT_FAILURE);
   }

   printf("Server is listening on port %d...\n", PORT);

   int client_socket = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
   if (client_socket<0)
   {
      perror("Accept failed");
      exit(EXIT_FAILURE);
   }

   while (1)
   {
      ssize_t len = recv(client_socket, buffer, BUFF_SIZE, 0);
      buffer[len] = '\0';
      printf("CLient: %s\n", buffer);
      printf("Server: ");
      fgets(buffer, BUFF_SIZE, stdin);
      send(client_socket, buffer, strlen(buffer), 0);
   }

   close(client_socket);
   close(sockfd);

   return 0;
}