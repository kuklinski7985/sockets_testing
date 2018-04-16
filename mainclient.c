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

int main(int argc, char const *argv[])
{
  int port1 = 8090;

  char recv_message[256] = {0};
  char send_message[256] = {0};
  static int counter1 = 0;
  
  struct_mess_t server_message;
  struct sockaddr_in sock_addr;    //struct that contains the port and Ip addr
  int sock_handle;                 //assigned socket tracking value
  int valread;                     //return value for read

  sock_handle = socket(AF_INET, SOCK_STREAM, 0);
  if(sock_handle < 0)
    {
      printf("Socket NOT Created\n");
    }

  sock_addr.sin_family = AF_INET;
  sock_addr.sin_port = htons(port1);

  //if(inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr)<=0)
  if(inet_pton(AF_INET, argv[1], &sock_addr.sin_addr)<=0)
    {
      printf("Invalid Address\n");
    }
  
  if(connect(sock_handle, (struct sockaddr*)&sock_addr, sizeof(sock_addr))<0)
    {
      printf("connection to server FAILED!\n");
    }

  //struct_mess_t client_message1;
  //strcpy(client_message1.message, "Message from client");
  //strcpy(client_message1.message, argv[2]);
  //client_message1.float_val = 90.345355;
  

  while(counter1 < 20)
  {
    //printf("client inside while %d\n",counter1);
    sprintf(send_message, "Client Name: %s FD: %d | Counter: %d",argv[2],sock_handle, counter1);
    send(sock_handle, send_message, strlen(send_message),0);
    //printf("message sent by client: %s\n",send_message);
    //client_message1.int_val = counter1;
    //send(sock_handle, &client_message1,sizeof(client_message1),0);

    counter1++;
    //valread = read(sock_handle,recv_message,256);
    //printf("Echoed Back: %s\n",recv_message);
    //usleep(100);
    sleep(2);

  }

  /*for(int i=0; i<10;i++)
  {

  send(sock_handle, &new_message, sizeof(new_message),0);


  valread = read(sock_handle, rec_message, 256);
  printf("%s\n",rec_message);
  valread = read(sock_handle, &server_message,sizeof(server_message));

  printf("%s\n",server_message.message);
  printf("%f\n",server_message.float_val);
  printf("%d\n",server_message.int_val);
  sleep(1);*/

//}



}
