#include<stdio.h>
#include<string.h>    // for strlen
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_addr
#include<unistd.h>    // for write
#include<pthread.h>   // for threading, link with lpthread

int new_socket;

int clientsCount=0;
int roomsCount=0;

struct client{
    int id;
    int soketID;
    char name[15];//username
};

struct room{
    char roomName[15];//roomName
    struct client allClients[5];
    int isPrivate;//1=public,0=private
    int clientCountinRoom;
    char password[10];
};

struct client allClients[2];
struct room allRooms[5];


void *connection_handler(void *socket_desc)
{
    //Get the socket descriptor
    int sock = *((int*)socket_desc);   
    char *message = "Greetings! I am your connection handler\n";;
    char client_message[2000];
    char command[15];
    int read_size = 0;
    while(1)
    {  
        read_size = recv(sock , client_message , 2000 , 0);
        client_message[read_size]='\0';
        printf("%s",client_message);

        if(strcmp("-create", command)==0){
            printf("2222");
        }

        else if(strcmp("-pcreate", client_message)==0){
            strcmp(command,client_message);
        } 

        else if(strcmp("-enter", client_message)==0){
            strcmp(command,client_message);
        } 

        else if(strcmp("-msg", client_message)==0){
            strcmp(command,client_message);
        } 

        else if(strcmp("-quit", client_message)==0){
            strcmp(command,client_message);
        } 

        else if(strcmp("-create", command)==0){
            struct room tempRoom;
            strcpy(tempRoom.roomName,client_message);
            tempRoom.isPrivate=1;
            tempRoom.clientCountinRoom=1;
            allRooms[roomsCount]=tempRoom;
            roomsCount++;
            
            printf("3");

            printf("%f",allRooms[0].roomName);

        } 

    }

    char *message = "Its my duty to communicate with you";
    write(sock , message , strlen(message));
    
    free(socket_desc); //Free the socket pointer     

    return 0;
}
int main(int argc, char *argv[])
{
    int socket_desc, c, *new_sock;
    struct sockaddr_in server, client;
    char *message;

     
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        puts("Could not create socket");
        return 1;
    }
     
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
     
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
{
        puts("Binding failed");
        return 1;
    }
     
    listen(socket_desc, 3);
     
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    while(new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))
    {
        //client tempClient = new client()
        struct client tempClient;
        tempClient.soketID = new_socket;
        allClients[clientsCount]=tempClient;
        clientsCount++;
        puts("Connection accepted");

        message = "Hello Client, I will assign a handler for you\n";
        write(new_socket, message, strlen(message));
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
         
        if(pthread_create(&sniffer_thread, NULL, connection_handler,(void*)new_sock) < 0)
        {
            puts("Could not create thread");
            return 1;
        }

        puts("Handler assigned");
    }
    return 0;
}