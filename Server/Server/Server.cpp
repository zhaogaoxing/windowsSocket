// Server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 1024

int _tmain(int argc, _TCHAR* argv[])
{
	//检查文件是否存在
	char* filename = "D:\\音乐\\send.txt";//文件名
	FILE* fp = fopen(filename,"rb");    //以二进制方式打开文件
	if (fp == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	char cmd[100] = { 0 };
	printf("输入命令（download）:");
	gets(cmd);
	printf(cmd);
	FILE*fpC;
	if (!cmd)
	{

		//先输入文件名，看文件是否能创建成功
		char filenameC[100] = { 0 };  //文件名
		printf("Input filename to save: ");
		gets(filenameC);
		fpC = fopen(filenameC, "wb");  //以二进制方式打开文件
		if (fpC == NULL)
		{
			printf("Cannot open file, press any key to exit!\n");
			system("pause");
			exit(0);
		}
	}

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
	int nCount;
	int nCountC;
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
		printf("接收到:%s\n",buffer);
		char* sendSuccess;
		if (buffer)
		{
			sendSuccess = "Success";
		}
		send(clntSock, sendSuccess, strLen + 10, 0);  //将数据原样返回
		closesocket(clntSock);
		memset(buffer, 0, BUF_SIZE);

		//向客户端传输数据
		while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0){
			send(clntSock, buffer, nCount, 0);
		}
		shutdown(clntSock,SD_SEND);//文件读取完毕，断开输出流，向客户端发送FIN包
		recv(clntSock, buffer, BUF_SIZE, 0);  //阻塞，等待客户端接收完毕

		//从客户端接受文件
		if ((nCountC = recv(servSock, buffer, BUF_SIZE, 0))-1 > 0)
		{
			while ((nCountC = recv(servSock, buffer, BUF_SIZE, 0)) > 0){
				fwrite(buffer, nCountC, 1, fpC);
			}
			printf("File transfer success!");
		}

	}

	//向客户端发送数据
	/*char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);*/

	//关闭套接字
	//closesocket(clntSock);
	fclose(fp);
	fclose(fpC);
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();
	system("pause");
	return 0;
}

