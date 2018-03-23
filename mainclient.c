#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <errno.h>
#include <signal.h>

#include "client_socket.h"

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

void main()
{
  int valread;
  int sock_handle;
  int port1 = 8090;

  char rec_message[256];
  char send_message[256] = "MESSGAES! to server from client!\n";
  
  sock_handle = client_socket_init(port1);

  send(sock_handle, send_message, 256,0);

  valread = read(sock_handle, rec_message, 256);
  printf("Message Received from Server: %s\n",rec_message);
}
