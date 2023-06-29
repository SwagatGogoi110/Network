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
   socklen_t server_len;

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if (sockfd<0)
   {
      perror("Socket creation failed");
      exit(EXIT_FAILURE);
   }

   memset(&server_addr, 0, sizeof(server_addr));

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(PORT);

   server_len = sizeof(server_addr);

   while (1)
   {
      printf("Enter a message: ");
      fgets(buffer, BUFF_SIZE, stdin);

      sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
      ssize_t len = recvfrom(sockfd, (char *)buffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &server_len);
      buffer[len] = '\0';

      printf("Reversed message from server:  %s\n", buffer);
   }

   close(sockfd);
   return 0;
}
