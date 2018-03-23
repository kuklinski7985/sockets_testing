/**
* @file server_socket.c
* @brief fxn definitions for initialization of socket server and usage
* @author Andrew Kuklinski
* @date 03/22/2018
**/

/*NOTES:
* - add errno error detection 
* - add signal processing for SIGUSR to change while loop exit variable to keep alive and processing
* - change the prototype in order to match the how it is called.  thread vs. function call
*/


#include "server_socket.h"

#define MYPORT 8090

void remote_socket_server_init()
{
  struct sockaddr_in addr;
  int opt = 1;
  int addrlen = sizeof(addr);
  int sock_handle;      //creates and initializes the server side socket
  int connected_sock;   //fd for newly connected socket, available for transfer
  int valread;

  char rec_message[256];
  char test_message[256] = "Stuff and things are awesome!";

  printf("Server Initialization Starting\n");
  
  if((sock_handle = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    printf("Socket Allocation Failed\n");
  }

  if(setsockopt(sock_handle, SOL_SOCKET, (SO_REUSEADDR | SO_REUSEPORT), &opt, sizeof(opt)))
  {
      printf("Error with Setsockopt\n");
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(MYPORT);

  if(bind(sock_handle, (struct sockaddr*)&addr,sizeof(addr))<0)
    {
      printf("error on bind\n");
       printf("bing errno %s\n", strerror(errno));
    }

  printf("Listening mode for server\n");
  listen(sock_handle,5);

//might have to add while loop where 
  if((connected_sock = accept(sock_handle, (struct sockaddr*) &addr, &addrlen)) <0)
    {
      printf("Accept failure\n");
    }

  valread = read(connected_sock,rec_message, 256);//strlen(rec_message));
  printf("message received from client: %s",rec_message);

  send(connected_sock, test_message, 256,0);
  printf("Message sent s / c\n");
  shutdown(connected_sock,3);
}
