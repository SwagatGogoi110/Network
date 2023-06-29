// simple Client and Server programs in C, to demonstrate the use of UDP Sockets.
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
    struct sockaddr_in server_addr, client_addr; // check 'netinet/in.h' for the struct
    socklen_t client_len = sizeof(client_addr);

    //Create socket 
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    //Configure server address
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Bind socket to the server address
    if (bind(sockfd,(const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening to port %d....\n",PORT);

    while(1){
        //Recieve message from client
        ssize_t len = recvfrom(sockfd,(char*)buffer,BUFF_SIZE,MSG_WAITALL,(struct sockaddr*)&client_addr,&client_len);
        buffer[len] = '\0';

        //Print the message
        printf("Recieved message from the client: %s\n",buffer);

        //Reversr the message 
        int i,j;
        char temp;
        for(i=0,j = strlen(buffer)-1;i<j;++i,--j){
            temp = buffer[i];
            buffer[i] = buffer[j];
            buffer[j] = temp;
        }
       
        //send reversed message back to the client
        sendto(sockfd, (const char*)buffer, strlen(buffer),0,(const struct sockaddr*)&client_addr,client_len);
        printf("Reversed message sent to client.\n");
    }

    //close socket 
    close(sockfd);

    return 0;
}
