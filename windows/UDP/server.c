#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8888
#define MAX_CLIENTS 5

int main()
{

    WSADATA wsaData;
    SOCKET serverSocket;
    SOCKADDR_IN serverAddr;
    int serverAddrSize;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    // serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    serverAddrSize = sizeof(serverAddr);

    while (1)
    {
        char buffer[256];
        int bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (SOCKADDR *)&serverAddr, &serverAddrSize);

        if (bytesReceived > 0)
        {
            // print the message received from the client
            printf("Received message from client: %s\n", buffer);
            // handle the message
            // ...
        }
        }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
