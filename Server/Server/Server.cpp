// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 100
int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	//sockAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",&sockAddr);  //具体的IP地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//进入监听状态
	listen(servSock, 20);

	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	//SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	char buffer[BUF_SIZE] = {0};
	//int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //接收客户端发来的数据
	/*char* sendSuccess;
	if (buffer)
	{
		sendSuccess = "Success";
	}*/
	//send(clntSock, sendSuccess, strLen+10, 0);  //将数据原样返回

	while (1)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //接收客户端发来的数据

		char* sendSuccess;
		if (buffer)
		{
			sendSuccess = "Success";
		}
		send(clntSock, sendSuccess, strLen + 10, 0);  //将数据原样返回
		closesocket(clntSock);
		memset(buffer, 0, BUF_SIZE);
	}

	//向客户端发送数据
	/*char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);*/

	//关闭套接字
	//closesocket(clntSock);
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();
	system("pause");
	return 0;
}

