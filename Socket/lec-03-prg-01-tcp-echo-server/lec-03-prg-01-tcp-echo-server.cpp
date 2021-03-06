#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

#define PORT 65456
#define BufferSize 1024
using namespace std;

int main()
{
	cout << "> echo-server is activated" << endl;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket;
	ServerSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN ServerSocketAddr = {};
	ServerSocketAddr.sin_family = AF_INET;
	ServerSocketAddr.sin_port = htons(PORT);
	ServerSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(ServerSocket, (SOCKADDR*)&ServerSocketAddr, sizeof(ServerSocketAddr));
	listen(ServerSocket, SOMAXCONN);

	SOCKADDR_IN ClientAddr = {};
	int ClientSize = sizeof(ClientAddr);
	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &(ClientSize));

	cout << "> Client connected IP address = " << inet_ntoa(ClientAddr.sin_addr) << " with Port Number " << ntohs(ClientAddr.sin_port) << endl;

	while (1)
	{
		char RecvData[BufferSize] = {};
		recv(ClientSocket, RecvData, BufferSize, 0);
		send(ClientSocket, RecvData, strlen(RecvData), 0);
		cout << "> echoed : " << RecvData << endl;
		if (strcmp(RecvData, "quit") == 0)
			break;
	}

	closesocket(ClientSocket);
	closesocket(ServerSocket);
	WSACleanup();

	cout << "> echo-server is de-activated" << endl;

	return 0;
}