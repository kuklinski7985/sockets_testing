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
  //char send_message[256] = "Client to Server: This is secret!\n";
  
  struct_mess_t server_message;


  struct_mess_t new_message;
  strcpy(new_message.message, "shit be cray!");
  new_message.float_val = 90.345355;
  new_message.int_val = 321;

  sock_handle = client_socket_init(port1);
  for(int i=0; i<10;i++)
  {

  send(sock_handle, &new_message, sizeof(new_message),0);


  valread = read(sock_handle, rec_message, 256);
  printf("%s\n",rec_message);
  valread = read(sock_handle, &server_message,sizeof(server_message));

  printf("%s\n",server_message.message);
  printf("%f\n",server_message.float_val);
  printf("%d\n",server_message.int_val);
  sleep(1);

}



}
