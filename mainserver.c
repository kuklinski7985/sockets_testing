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

void main()
{
  int valread;
  int connected_sock;
  int port1 = 8090;

  char rec_message[256];
  char test_message[256] = "Stuff and things are awesome!";

  connected_sock = remote_socket_server_init(port1);
  valread = read(connected_sock,rec_message, 256);
  printf("message received from client: %s",rec_message);

  send(connected_sock, test_message, 256,0);
  printf("Message sent s / c\n");
  shutdown(connected_sock,3);
}
