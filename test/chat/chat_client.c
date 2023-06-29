#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024
#define PORT 8080

int main()
{
   int sockfd;
   char buffer[BUFF_SIZE];
   struct sockaddr_in server_addr;
   socklen_t server_len = sizeof(server_addr);

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      perror("Socket creation failed");
      exit(EXIT_FAILURE);
   }

   memset(&server_addr, 0, sizeof(server_addr));

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(PORT);

   if(connect(sockfd, (struct sockaddr*)&server_addr, server_len) <0){
      perror("Connection failed");
      exit(EXIT_FAILURE);
   }

   while (1)
   {
      printf("Client: ");
      fgets(buffer, BUFF_SIZE, stdin);

      send(sockfd, buffer, strlen(buffer), 0);

      ssize_t len = recv(sockfd, buffer, BUFF_SIZE, 0);
      buffer[len] = '\0';

      printf("Server: %s\n", buffer);
   }
   
   close(sockfd);

   return 0;
}