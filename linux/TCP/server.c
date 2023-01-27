#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888
#define MAX_CLIENTS 5

int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrSize;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, MAX_CLIENTS);

    clientAddrSize = sizeof(clientAddr);

    while (1)
    {
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrSize);

        if (clientSocket >= 0)
        {
            // handle client request
            // ...
            close(clientSocket);
        }
    }

    close(serverSocket);

    return 0;
}
