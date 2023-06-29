//Write a simple Chatting Program in C, using sockets.

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
    struct sockaddr_in server_addr,client_addr;
    socklen_t client_len = sizeof(client_addr);
    socklen_t server_len = sizeof(server_addr);


    //create socket
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));
    memset(&client_addr,0,sizeof(client_addr));

    //Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Bind socket to the server address
    if(bind(sockfd,(const struct sockaddr*)&server_addr,server_len)<0){
        perror("Bind Failed");
        exit(EXIT_FAILURE);
    }

    //Create connection queue
    if(listen(sockfd,5)<0){
        perror("Error in Listening");
        exit(EXIT_FAILURE);
    } //5 is maximum connection queue size

    printf("Server listening on port %d...\n",PORT);

    //accept incoming/client connection

    int client_socket = accept(sockfd,(struct sockaddr*)&client_addr,&client_len);
    if(client_socket < 0 ){
        perror("Acccept failed");
        exit(EXIT_FAILURE);
    }

    //Recieve and Send message
    while(1){
        //Recieve from client
        ssize_t len = recv(client_socket,buffer,BUFF_SIZE,0);
        buffer[len] = '\0';

        //Print recieved message
        printf("Client: %s\n",buffer);

        //Get input from server
        printf("Server: ");
        fgets(buffer,BUFF_SIZE,stdin);

        //Send from server
        send(client_socket,buffer,strlen(buffer),0);

    }
    close(client_socket);
    close(sockfd);

    return 0;
}
