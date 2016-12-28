// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	//sockAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",&sockAddr);  //�����IP��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	//��ͻ��˷�������
	char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();
	system("pause");
	return 0;
}

