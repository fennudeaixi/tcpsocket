//1 保证 winsocke2在windwos.h之前
//2 WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
using namespace std;

int main()
{
	//生成widows socket环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);



	
	WSACleanup();

	return 0;
}