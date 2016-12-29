// Server.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#define BUF_SIZE 1024

int _tmain(int argc, _TCHAR* argv[])
{
	//����ļ��Ƿ����
	char* filename = "D:\\����\\send.txt";//�ļ���
	FILE* fp = fopen(filename,"rb");    //�Զ����Ʒ�ʽ���ļ�
	if (fp == NULL)
	{
		printf("Cannot open file, press any key to exit!\n");
		system("pause");
		exit(0);
	}

	char cmd[100] = { 0 };
	printf("�������download��:");
	gets(cmd);
	printf(cmd);
	FILE*fpC;
	if (!cmd)
	{

		//�������ļ��������ļ��Ƿ��ܴ����ɹ�
		char filenameC[100] = { 0 };  //�ļ���
		printf("Input filename to save: ");
		gets(filenameC);
		fpC = fopen(filenameC, "wb");  //�Զ����Ʒ�ʽ���ļ�
		if (fpC == NULL)
		{
			printf("Cannot open file, press any key to exit!\n");
			system("pause");
			exit(0);
		}
	}

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
	//SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	char buffer[BUF_SIZE] = {0};
	int nCount;
	int nCountC;
	//int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //���տͻ��˷���������
	/*char* sendSuccess;
	if (buffer)
	{
		sendSuccess = "Success";
	}*/
	//send(clntSock, sendSuccess, strLen+10, 0);  //������ԭ������

	while (1)
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //���տͻ��˷���������
		printf("���յ�:%s\n",buffer);
		char* sendSuccess;
		if (buffer)
		{
			sendSuccess = "Success";
		}
		send(clntSock, sendSuccess, strLen + 10, 0);  //������ԭ������
		closesocket(clntSock);
		memset(buffer, 0, BUF_SIZE);

		//��ͻ��˴�������
		while ((nCount = fread(buffer, 1, BUF_SIZE, fp)) > 0){
			send(clntSock, buffer, nCount, 0);
		}
		shutdown(clntSock,SD_SEND);//�ļ���ȡ��ϣ��Ͽ����������ͻ��˷���FIN��
		recv(clntSock, buffer, BUF_SIZE, 0);  //�������ȴ��ͻ��˽������

		//�ӿͻ��˽����ļ�
		if ((nCountC = recv(servSock, buffer, BUF_SIZE, 0))-1 > 0)
		{
			while ((nCountC = recv(servSock, buffer, BUF_SIZE, 0)) > 0){
				fwrite(buffer, nCountC, 1, fpC);
			}
			printf("File transfer success!");
		}

	}

	//��ͻ��˷�������
	/*char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);*/

	//�ر��׽���
	//closesocket(clntSock);
	fclose(fp);
	fclose(fpC);
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();
	system("pause");
	return 0;
}

