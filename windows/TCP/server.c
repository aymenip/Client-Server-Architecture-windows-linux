#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8888
#define MAX_CLIENTS 5

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		puts("Enter Valid Server ip");
		return 0;
	}
	// const char *IP = argv[0];
	// const int *PORT = argv[1];

	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	// serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// serverAddr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	// serverAddr.sin_port = htons((int)argv[2]);

	bind(serverSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
	listen(serverSocket, MAX_CLIENTS);

	clientAddrSize = sizeof(clientAddr);

	clientSocket = accept(serverSocket, (SOCKADDR *)&clientAddr, &clientAddrSize);

	while (1)
	{
		if (clientSocket != INVALID_SOCKET)
		{
			char buffer[256];
			int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (bytesReceived > 0)
			{
				// Get the IP address of the client
				SOCKADDR_IN client_address;
				int client_address_len = sizeof(client_address);
				getpeername(clientSocket, (SOCKADDR *)&client_address, &client_address_len);
				char *client_ip = inet_ntoa(client_address.sin_addr);
				printf("Received message from client [%s]: %s\n", client_ip, buffer);
			}

			char response[] = "Hello";
			int bytesSent = send(clientSocket, response, strlen(response), 0);
			if (bytesSent > 0)
			{
				printf("Response sent to client: %s\n", response);
			}
		}
	}
	closesocket(clientSocket);
	WSACleanup();

	return 0;
}
