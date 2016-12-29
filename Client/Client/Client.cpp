// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

#define BUF_SIZE 1024

int _tmain(int argc, _TCHAR* argv[])
{
	//先检查文件是否存在
	char*filenameS = "D:\\音乐\\send.md";  //文件名
	FILE*fpS = fopen(filenameS,"rb");
	if (fpS==NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);

	}


	//先输入文件名，看文件是否能创建成功
	char filename[100] = { 0 };  //文件名
	printf("Input filename to save: ");
	gets(filename);
	FILE *fp = fopen(filename, "wb");  //以二进制方式打开（创建）文件
	if (fp==NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}


	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	//SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	//sockAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",&sockAddr);
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };

	char buffer[BUF_SIZE] = { 0 };  //文件缓冲区
	int nCount;
	int nCountS;
	while (1)
	{
		//创建套接字
		SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
		printf("Input a string:");
		scanf("%s", bufSend);
		send(sock, bufSend, strlen(bufSend), 0);
		recv(sock, bufRecv, BUF_SIZE, 0);
		printf("Message form server: %s\n", bufRecv);

		memset(bufSend,0,BUF_SIZE);
		memset(bufRecv,0,BUF_SIZE);
		closesocket(sock);

		while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0)
		{
			fwrite(buffer, nCount, 1, fp);
		}
		puts("File transfer success!");
		

		//发送给服务端文件
		while ((nCountS = fread(buffer, 1, BUF_SIZE, fpS)) > 0)
		{
			send(sock, buffer, nCount, 0);
		}
		shutdown(sock,SD_SEND);
		recv(sock,buffer,BUF_SIZE,0);
	}

	//connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//获取用户输入的字符串并发送给服务器
	//char bufSend[BUF_SIZE] = { 0 };
	/*printf("Input a string:");
	scanf("%s",bufSend);
	send(sock,bufSend,strlen(bufSend),0);*/

	//接收服务器传回的数据
	//char bufRecv[BUF_SIZE] = { 0 };
	//recv(sock, bufRecv, BUF_SIZE, 0);

	//输出接收到的数据
	printf("Message form server: %s\n", bufRecv);

	//关闭套接字
	//closesocket(sock);
	fclose(fp);
	fclose(fpS);
	//终止使用 DLL
	WSACleanup();

	system("pause");
	return 0;
}

