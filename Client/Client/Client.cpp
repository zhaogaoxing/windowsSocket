// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#define BUF_SIZE 1024

int _tmain(int argc, _TCHAR* argv[])
{
	//�ȼ���ļ��Ƿ����
	char*filenameS = "D:\\����\\send.md";  //�ļ���
	FILE*fpS = fopen(filenameS,"rb");
	if (fpS==NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);

	}


	//�������ļ��������ļ��Ƿ��ܴ����ɹ�
	char filename[100] = { 0 };  //�ļ���
	printf("Input filename to save: ");
	gets(filename);
	FILE *fp = fopen(filename, "wb");  //�Զ����Ʒ�ʽ�򿪣��������ļ�
	if (fp==NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}


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

	char buffer[BUF_SIZE] = { 0 };  //�ļ�������
	int nCount;
	int nCountS;
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

		while ((nCount = recv(sock, buffer, BUF_SIZE, 0)) > 0)
		{
			fwrite(buffer, nCount, 1, fp);
		}
		puts("File transfer success!");
		

		//���͸�������ļ�
		while ((nCountS = fread(buffer, 1, BUF_SIZE, fpS)) > 0)
		{
			send(sock, buffer, nCount, 0);
		}
		shutdown(sock,SD_SEND);
		recv(sock,buffer,BUF_SIZE,0);
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
	fclose(fp);
	fclose(fpS);
	//��ֹʹ�� DLL
	WSACleanup();

	system("pause");
	return 0;
}

