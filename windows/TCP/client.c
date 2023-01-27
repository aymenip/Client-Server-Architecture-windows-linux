#include <winsock2.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		puts("Enter Valid Server ip");
		return 0;
	}
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddr;
	char buffer[256];
	int responseLength;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	connect(clientSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr));

	if (clientSocket >= 1)
	{
		while (1)
		{
			{
				printf("Enter a message: ");
				gets(buffer);
				send(clientSocket, buffer, strlen(buffer), 0);
				if (buffer[0] == '#')
				{
					break;
				}
			}
			responseLength = recv(clientSocket, buffer, sizeof(buffer), 0);
			if (responseLength >= 1)
			{
				printf("Server response [%s]: %s\n", SERVER_IP, buffer);
			}
		}

		closesocket(clientSocket);
	}
	WSACleanup();
	return 0;
}
