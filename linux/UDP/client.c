#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main()
{
     int clientSocket;
     struct sockaddr_in serverAddr;
     char buffer[256] = "hi";

     clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

     serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
     serverAddr.sin_family = AF_INET;
     serverAddr.sin_port = htons(PORT);

     while (1)
     {
          printf("Enter a message: ");
          gets(buffer);
          sendto(clientSocket, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

          if (buffer[0] == '#')
          {
               close(clientSocket);
               break;
          }
     }

     return 0;
}
