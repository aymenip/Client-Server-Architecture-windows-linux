#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main()
{
     char buffer[256];

     // gets(buffer);

     WSADATA wsaData;
     SOCKET clientSocket;
     SOCKADDR_IN serverAddr; // ip address information

     WSAStartup(MAKEWORD(2, 2), &wsaData);

     clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

     serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
     serverAddr.sin_family = AF_INET;
     serverAddr.sin_port = htons(PORT);
     while (1)
     {

          printf("Enter message to send: ");
          gets(buffer);
          sendto(clientSocket, buffer, strlen(buffer), 0, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
          if (buffer[0] == "#")
          {
               closesocket(clientSocket);
               WSACleanup();
               break;
          }
          int responseLength = recv(clientSocket, buffer, sizeof(buffer), 0);
          if (responseLength >= 1)
          {
               buffer[responseLength] = '\0';
               printf("Server response: %s\n", buffer);
          }
     }

     return 0;
}
