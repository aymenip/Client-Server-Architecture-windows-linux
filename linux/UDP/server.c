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
    int serverSocket;
    struct sockaddr_in serverAddr;
    socklen_t serverAddrSize;

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    serverAddrSize = sizeof(serverAddr);

    while (1)
    {
        char buffer[256];
        int bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddr, &serverAddrSize);

        if (bytesReceived > 0)
        {
            // print the message received from the client
            printf("Received message from client: %s\n", buffer);
            // handle the message
            // ...
            // send response to client
            char response[] = "Hello";
            int bytesSent = sendto(serverSocket, response, strlen(response), 0, (struct sockaddr *)&serverAddr, serverAddrSize);
            if (bytesSent > 0)
            {
                printf("Response sent to client: %s\n", response);
            }
        }
    }

    close(serverSocket);

    return 0;
}
