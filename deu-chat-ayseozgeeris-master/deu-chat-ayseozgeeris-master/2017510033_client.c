#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h> // for inet_addr
#include<pthread.h> 

int socket_desc;

void *receive_handler(){

    char server_message[2000];
    int read_size;
    while( (read_size = recv(socket_desc , server_message , 2000 , 0)) > 0 )
    {
        //Send the message back to client
        printf(server_message);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    struct sockaddr_in server;
     
    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        puts("Could not create socket");
        return 1;
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("Connection error");
        return 1;
    }
    char nickname[15];
    printf("Enter a nickname\n");
    scanf("%s", nickname);*/
    
    puts("Connected");

    pthread_t sniffer_thread;
    if(pthread_create(&sniffer_thread, NULL, receive_handler,NULL) < 0)
    {
        puts("Could not create thread");
        return 1;
    }

    char input[15];//-cretae
    char input2[15];//roomname
    char inputBefore[15];//-create roomname
    
    while(1){

        fgets(input,15,stdin); //inputu bosluga göre split edilmesi lazim ve ilk elemanı cekmek gerek 
        
        write(socket_desc, input, strlen(input));
        if(strcmp("-list", input)==0){
            printf("Rooms: \n");
        } 

        else if(strcmp("-create", input)==0){
            printf("New room created.\n");            
            write(socket_desc, "-create.", strlen("-create."));           
            ptr=strtok(NULL, " ");   
            write(socket_desc, ((void *)ptr), strlen((void *)ptr));
        } 

        else if(strcmp("-pcreate", input)==0){
            printf("Private rrom created. \n");
        }        

        else if(strcmp("-enter", input)==0){
            printf("<you entered the room. \n");
        }  

        else if(strcmp("-quit", input)==0){
            printf("You quited the room. ");
        }  

        else if(strcmp("-msg", input)==0){
            printf("Message \n");
        }  

        else if(strcmp("-whoami", input)==0){
            printf("Nick name ");
        }  

        else if(strcmp("-exit", input)==0){
            printf("Exit \n");
        }  
    }
    return 0;
}

