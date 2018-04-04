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

  //char rec_message[256];
  struct_mess_t rec_message;
  char send_message[256] = "Server: Thank you for your message client!\n";
  struct_mess_t send_struct_message;
  strcpy(send_struct_message.message, "zen out bro.");
  send_struct_message.float_val = 145.4333333;
  send_struct_message.int_val = 89;

  connected_sock = remote_socket_server_init(port1);
  valread = read(connected_sock,&rec_message, sizeof(rec_message));
  printf("%s\n",rec_message.message);
  printf("%f\n",rec_message.float_val);
  printf("%d\n",rec_message.int_val);

  send(connected_sock,send_message, 256,0);
  //printf("Message sent s / c\n");

  send(connected_sock, &send_struct_message, sizeof(send_struct_message),0);  
  shutdown(connected_sock,3);
}
