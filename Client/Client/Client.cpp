// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#define BUF_SIZE 100

int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	//SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	//sockAddr.sin_addr.s_addr = inet_pton(AF_INET, "127.0.0.1",&sockAddr);
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

	char bufSend[BUF_SIZE] = { 0 };
	char bufRecv[BUF_SIZE] = { 0 };

	while (1)
	{
		//�����׽���
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
	}

	//connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//��ȡ�û�������ַ��������͸�������
	//char bufSend[BUF_SIZE] = { 0 };
	/*printf("Input a string:");
	scanf("%s",bufSend);
	send(sock,bufSend,strlen(bufSend),0);*/

	//���շ��������ص�����
	//char bufRecv[BUF_SIZE] = { 0 };
	//recv(sock, bufRecv, BUF_SIZE, 0);

	//������յ�������
	printf("Message form server: %s\n", bufRecv);

	//�ر��׽���
	//closesocket(sock);

	//��ֹʹ�� DLL
	WSACleanup();

	system("pause");
	return 0;
}

