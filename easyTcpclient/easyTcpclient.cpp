
#include <Windows.h>
#include <WinSock2.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
int main()
{
	//生成widows socket环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//1创建一个socket套接字
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//2 connect 服务器
	sockaddr_in _sin;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(12345);//网络字节序
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = connect(_sock, (sockaddr *)(&_sin), sizeof(sockaddr_in));

	char cmdBuf[128] = {};
	while (1)
	{
		scanf("%s", cmdBuf);
		if (strcmp(cmdBuf, "exit") != 0)
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		else 
			break;

		char recvBuf[256] = {};
		int nlen = recv(_sock, recvBuf, sizeof(recvBuf), 0);
		if (nlen > 0)
			std::cout << recvBuf;

	}
	

	//关闭套接字
	closesocket(_sock);

	WSACleanup();
	getchar();
	return 0;
}