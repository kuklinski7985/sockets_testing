#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h> 
#include <netinet/in.h> 
#include <sys/time.h>
#include <arpa/inet.h>

#include "server_socket.h"

//server side
/*create a init function that takes a port number and IP address
and returns a socke handler identifier.  
include functionality for errno and 
main function should only be calling the init function and processing data 
from the client*/


//client side 

/*mainclient.c will utilize the client socket library and struct definitions
  to keep things independant*/
/* stand alone program that sends requests to client
both client and server should be able to send and receive
structs of predefined type, independant of use on either end.*/

#define MAX_NUM_CLIENTS  10
int main(int argc, char const *argv[])
{
  int valread;
  int sock_handle;      //creates and initializes the server side socket
  int new_request_connection;  //fd for newly connected socket, available for transfer
  int port1 = 8090;     
  int i;
  int new_activity;   //value of ready descriptors that select returns
  int connected_clients_fd[MAX_NUM_CLIENTS];
  struct sockaddr_in addr;
  int opt = 1;
  int addrlen = sizeof(addr);
  fd_set readfds;
  char send_mess[256];
  char recv_message[256];
  
  printf("Server Initialization Starting\n");
  
  //socket returns file descriptor for the new socket, -1 error
  if((sock_handle = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  //if((sock_handle = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == 0)
  {
    printf("Socket Allocation Failed\n");
  }

  if(setsockopt(sock_handle, SOL_SOCKET, (SO_REUSEADDR | SO_REUSEPORT), &opt, sizeof(opt)))
  {
      printf("Error with Setsockopt\n");
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port1);

  if(bind(sock_handle, (struct sockaddr*)&addr,sizeof(addr))<0)
    {
      printf("error on bind\n");
       printf("bind errno %s\n", strerror(errno));
    }

  printf("Listening mode for server\n");
  listen(sock_handle,5);

  //adds the main socket descriptor to the watch list
  FD_SET(sock_handle, &readfds);

  while(1)
  {
    //new_activity = select(MAX_NUM_CLIENTS+1, &readfds, NULL, NULL, NULL);
    //printf("New activity %d\n",new_activity);
    //printf("ERROR: %s\n", strerror(errno));

    //checks to see if there is a client asking for a connection
    if(FD_ISSET(sock_handle,&readfds))
    {
      if((new_request_connection = accept(sock_handle, (struct sockaddr*) &addr, &addrlen)) <0)
      {
        printf("new connection failed");
      }
      printf("Accepted Connection: socket | ip | port : %d | %s | %d\n",new_request_connection, inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

      for(i=0; i<MAX_NUM_CLIENTS;i++)
      {
        if(connected_clients_fd[i]==0)
        {
          connected_clients_fd[i] = new_request_connection;
          FD_SET(connected_clients_fd[i],&readfds);
        }
      }
    }
    //new_activity = select(MAX_NUM_CLIENTS+1, &readfds, NULL, NULL, NULL);
    //printf("New activity %d\n",new_activity);
    //printf("ERROR: %s\n", strerror(errno));
  

    for(i=0;i<MAX_NUM_CLIENTS;i++)
    {
      printf("server inside for %d",i);
      if(FD_ISSET(connected_clients_fd[i],&readfds))
      {
        valread = read(connected_clients_fd[i],recv_message,256);
        printf("%s\n",recv_message);
        //recv_message[valread] = '\0';
        //send(connected_clients_fd[i],recv_message,strlen(recv_message),0);
      }
      
    }


  } 
}



























/*
//initializing connected clients array to zero
for(i=0; i < MAX_NUM_CLIENTS; i++)
{
  connected_clients_fd[i] = 0;

}

  //accept returns non- file descriptor for the accepted socket, -1 error
  //accept has been set up as non-blocking shoul only check the once and move on
  if((new_request_connection = accept(sock_handle, (struct sockaddr*) &addr, &addrlen)) <0)
  {
    printf("Accept failure\n");
  }
  printf("Accepted Connection: socket | ip | port : %d | %s | %d\n",new_request_connection, inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));



while(1)
{
  //this will check if the new client request already exists in the array, add if not, and set
  for(i=0; i < MAX_NUM_CLIENTS; i++)
  {
    if(connected_clients_fd[i] == 0)
    {
      connected_clients_fd[i] = new_request_connection;
      FD_SET(connected_clients_fd[i],&readfds);
    }

  }
  //select blocks until new activity is detected on any of the connected sockets
  new_activity = select(MAX_NUM_CLIENTS+1, &readfds, NULL, NULL, NULL);

  //once new activiey is detected, process all pending requests and run another loop

  for(i=0; i<MAX_NUM_CLIENTS; i++)
  {
    if(FD_ISSET(connected_clients_fd[i],&readfds))
    {
      printf("[CLIENT] : response message");
      FD_CLR(connected_clients_fd[i],&readfds);
    }
  }

}

    if((new_request_connection = accept(sock_handle, (struct sockaddr*) &addr, &addrlen)) <0)
      {
        printf("Accept failure\n");
      }
    printf("Accepted Connection: socket | ip | port : %d | %s | %d\n",new_request_connection, inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
    while(1)
{
      printf("Accepted Connection: socket | ip | port : %d | %s | %d\n",new_request_connection, inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));

    struct_mess_t rec_message;
    char send_message[256] = "Server: Thank you for your message client!\n";
    struct_mess_t send_struct_message;
    strcpy(send_struct_message.message, "zen out bro.");
    send_struct_message.float_val = 145.4333333;
    send_struct_message.int_val = 89;

    valread = read(new_request_connection,&rec_message, sizeof(rec_message));
    printf("%s\n",rec_message.message);
    printf("%f\n",rec_message.float_val);
    printf("%d\n",rec_message.int_val);

    send(new_request_connection,send_message, 256,0);

    send(new_request_connection, &send_struct_message, sizeof(send_struct_message),0);  
}
    shutdown(new_request_connection,3);
  
}*/
