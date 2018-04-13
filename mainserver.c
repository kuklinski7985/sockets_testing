#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <signal.h>

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

int main(int argc, char const *argv[])
{
  int valread;
  int connected_sock;  //fd for newly connected socket, available for transfer
  int port1 = 8090;     

  struct sockaddr_in addr;
  int opt = 1;
  int addrlen = sizeof(addr);
  int sock_handle;      //creates and initializes the server side socket

  printf("Server Initialization Starting\n");
  
  if((sock_handle = socket(AF_INET, SOCK_STREAM, 0)) == 0)  //or SOCK_STREAM | SOCK_NONBLOCK
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
       printf("bing errno %s\n", strerror(errno));
    }

  printf("Listening mode for server\n");
  listen(sock_handle,5);

  if((connected_sock = accept(sock_handle, (struct sockaddr*) &addr, &addrlen)) <0)
    {
      printf("Accept failure\n");
    }
  struct_mess_t rec_message;
  char send_message[256] = "Server: Thank you for your message client!\n";
  struct_mess_t send_struct_message;
  strcpy(send_struct_message.message, "zen out bro.");
  send_struct_message.float_val = 145.4333333;
  send_struct_message.int_val = 89;

  valread = read(connected_sock,&rec_message, sizeof(rec_message));
  printf("%s\n",rec_message.message);
  printf("%f\n",rec_message.float_val);
  printf("%d\n",rec_message.int_val);

  send(connected_sock,send_message, 256,0);

  send(connected_sock, &send_struct_message, sizeof(send_struct_message),0);  
  shutdown(connected_sock,3);
}
