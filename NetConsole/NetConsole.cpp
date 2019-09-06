// NetConsole.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <WINSOCK2.H>  
#include <Windows.h>  
#pragma comment(lib,"WS2_32.lib")  

#include <stdio.h>
#include <iostream>
#include <cmath>

SOCKET sockClient;
SOCKADDR_IN servAddr; // �������׽��ֵ�ַ

#define LOCAL_IP		"192.168.1.11"
#define LOCAL_PORT		8600
#define RST_OK			(0)
#define RST_PARAM_ERROR	(-1)
#define RST_CMD_INVALID	(-2)
#define RST_EXIT		(1)
#define RST_HELP		(2)

int ConnectServer(char * ip, unsigned int port)
{
	WSADATA wsd;    
	// ��ʼ���׽��ֶ�̬��  
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)  
    {  
        printf("WSAStartup failed !/n");  
        return 1;  

    }  
	// �����׽���  
    sockClient = socket(AF_INET,SOCK_DGRAM,0);  
    if(sockClient == INVALID_SOCKET)  
    {  
        printf("socket() failed, Error Code:%d/n",WSAGetLastError());  
        return 1;  
    }  

	// ���÷�������ַ  
    servAddr.sin_family = AF_INET;  
    servAddr.sin_addr.S_un.S_addr = inet_addr(ip);  
    servAddr.sin_port = htons(port);
	return 0;
}

int SendParam(char * buff, unsigned int len)
{
	int nRst = 0;
	char rxBuff[64];
	// ���������������  
    int nServAddLen = sizeof(servAddr);  
	if(sendto(sockClient, buff, len, 0, (sockaddr *)&servAddr, nServAddLen) == SOCKET_ERROR){  
        printf("sendto() failed:%d\n",WSAGetLastError());  
        closesocket(sockClient);  
        WSACleanup();  
        return -1;  
    } 
	memset(rxBuff, 0, sizeof(char)*64);
	nRst = recvfrom(sockClient, rxBuff, 64, 0, (sockaddr *)&servAddr, &nServAddLen);  
    if(SOCKET_ERROR == nRst)     
    {     
        printf("recvfrom failed !\n");     
        closesocket(sockClient);     
        WSACleanup();     
        return -1;     
    }  

	if (strcmp(rxBuff, "Help") == 0){
		return RST_HELP;
	}
	else if (strcmp(rxBuff, "Exit") == 0){
		return RST_EXIT;
	}
	else {
		// ��ӡ���Է���˷�����������  
		printf("result:%s\n", rxBuff); 
	}
  
	return RST_OK;
}

void Help()
{
	printf("workmode -- ����ģʽ��ս��ģʽ���ͽػ�\n");
	printf("transmode -- ����ģʽ������͸����\n");
	printf("mode -- ģʽ����Ƶ����Ƶ��\n");
	printf("freq -- Ƶ������\n");
	printf("speed -- ��������\n");
	printf("bw -- ��������\n");
	printf("localip -- ����IP\n");
	printf("localport -- ���ض˿�\n");
	printf("mac -- MAC��ַ\n");
	printf("remoteip -- ��λ��IP\n");
	printf("remoteport -- ��λ���˿�\n");
	printf("netid -- ����ID\n");
	printf("netsize -- �����ģ\n");
	printf("\n");
}

int CheckParamValid(char * cmdline)
{
	int i = 0,length = strlen(cmdline);

	for (i=0; i<length; i++){
		if (cmdline[i] == ' '){
			break;
		}
	}

	if (i == (length-1)){
		return true;
	}

	for (; i<length; i++){
		char c = cmdline[i];
		if ((c >= '0' && c <= '9')
			|| (c >= 'a' && c <= 'f')
			|| (c == ' ')){
				continue;
		}
		else {
			return false;
		}
	}

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int cmdLength = 0, nRst = 0;
	char c, cmdLine[256];

	ConnectServer(LOCAL_IP, LOCAL_PORT);
	Help();
	while (1){
		memset(cmdLine, 0, sizeof(char)*256);
		cmdLength = 0;
		printf(">>>������ָ��:");
		do {
			c = getchar();
			cmdLine[cmdLength++] = c;
		}while(c != '\n');

		if (cmdLine[0] == '\n'){
			//ֱ�������˻س�
			continue;
		}

		//����ָ��
		//����'\n'�滻�ɿո���ʶ�����Ĳ���
		cmdLine[cmdLength-1] = ' ';

		if (CheckParamValid(cmdLine) == false){
			printf("\nError:����������Ϸ�\n");
			continue;
		}

		nRst = SendParam(cmdLine, strlen(cmdLine));
		if (nRst == RST_HELP){
			Help();
		}
		else if (nRst == RST_EXIT){
			break;
		}
	}
	return 0;
}
