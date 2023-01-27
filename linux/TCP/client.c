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

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    send(clientSocket, buffer, strlen(buffer), 0);

    close(clientSocket);

    return 0;
}
