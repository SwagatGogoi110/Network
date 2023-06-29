#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // socket(), bind()
#include <netinet/in.h> //struct sockaddr_in
#include <unistd.h> 
#include <arpa/inet.h> // inet_addr(), htons()

#define BUFF_SIZE 1024
#define PORT 8080

int main(){
    int sockfd;
    char buffer[BUFF_SIZE];
    struct sockaddr_in server_addr; // check 'netinet/in.h' for the struct
    socklen_t server_len;

    // Create socket
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));

    //Configure server address
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    server_len= sizeof(server_addr);

    while (1)
    {
       printf("Enter a message: ");
       fgets(buffer,BUFF_SIZE,stdin);

       //Send message to server
        sendto(sockfd, (const char*)buffer, strlen(buffer),0,(const struct sockaddr*)&server_addr,sizeof(server_addr));

        //Recieve reverse message from server
        ssize_t len = recvfrom(sockfd,(char*)buffer,BUFF_SIZE,MSG_WAITALL,(struct sockaddr*)&server_addr,&server_len);
        buffer[len] = '\0';

        //Print reversed message
        printf("Reversed message from server:  %s\n",buffer);
    }
    
    //close socket
    close(sockfd);

    return 0;

}