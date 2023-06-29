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
   struct sockaddr_in server_addr, client_addr;
   socklen_t client_len = sizeof(client_addr);

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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

   if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
   {
      perror("Bind Failed");
      exit(EXIT_FAILURE);
   }

   printf("Server is listening on port %d...\n", PORT);

   while (1)
   {
      ssize_t len = recvfrom(sockfd, (char*)buffer, BUFF_SIZE, MSG_WAITALL, (struct sockaddr*)&client_addr, &client_len);
      buffer[len] = '\0';
      printf("CLient: %s\n", buffer);

      int i, j;
      char temp;
      for (i = 0, i < strlen(buffer) - 1; i < j; ++i, --j)
      {
         temp = buffer[i];
         buffer[i] = buffer[j];
         buffer[j] = temp;
      }

      sendto(sockfd, (const char*)buffer, strlen(buffer), 0, (const struct sockaddr*)&client_addr, client_len);
      printf("Reversed message send.\n");
   }

   close(sockfd);

   return 0;
}