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
    struct sockaddr_in server_addr;
    socklen_t server_len = sizeof(server_addr);

    //Create sockete
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));

    //Configure the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Connect to the server
    if(connect(sockfd,(struct sockaddr*)&server_addr,server_len)<0){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    //Recieve and send messages
    while(1){
        //Get input from client
        printf("Client: ");
        fgets(buffer,BUFF_SIZE,stdin);

        //Send message to server
        send(sockfd,buffer,strlen(buffer),0);

        //Recieve from server
        ssize_t len = recv(sockfd,buffer,BUFF_SIZE,0);
        buffer[len]='\0';

        //Print recieved message
        printf("Server: %s\n",buffer);
    }

    close(sockfd);

    return 0;
}