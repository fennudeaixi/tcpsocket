//1 保证 winsocke2在windwos.h之前
//2 WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN //属性 c/c++ ->预处理器 //尽量去使用新的socket库

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <Windows.h>
#include <WinSock2.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#pragma pack(1)
struct DataPackage
{
	int age;
	char name[32];
};

int main()
{
	//生成widows socket环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	//1创建一个socket套接字
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_sock < 0)
	{
		std::cout << "socket err";
		return _sock;
	}
	//2 bind一个端口
	sockaddr_in _sin;
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(12345);//网络字节序
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//INADDR_ANY
	int ret = bind(_sock, (sockaddr *)(&_sin), sizeof(sockaddr));
	if (ret)
	{
		std::cout << " bind err";
		return ret;
	}
	//3监听网络端口
	listen(_sock, 128);

	//4接收客户端连接
	sockaddr_in clientAddr;
	int cli_len =  sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	_cSock = accept(_sock, (sockaddr *)(&clientAddr), &cli_len);
	std::cout << "new client :" << inet_ntoa(clientAddr.sin_addr) << "access" << std::endl;

	char _recvBuf[128] = {};
	int nLen = 0;
	while (1)
	{
		nLen = recv(_cSock, _recvBuf, sizeof(_recvBuf), 0);

		//处理请求
		if (0 == strcmp(_recvBuf, "getinfo"))
		{
			DataPackage dp = { 80,"123" };
			send(_cSock, (const char *)&dp, sizeof(dp), 0);
		}
		
		
	}
	
	//6 关闭socket //111
	closesocket(_sock);

	WSACleanup();

	return 0;
}