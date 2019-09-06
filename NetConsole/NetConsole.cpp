// NetConsole.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <WINSOCK2.H>  
#include <Windows.h>  
#pragma comment(lib,"WS2_32.lib")  

#include <stdio.h>
#include <iostream>
#include <cmath>

SOCKET sockClient;
SOCKADDR_IN servAddr; // 服务器套接字地址

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
	// 初始化套接字动态库  
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)  
    {  
        printf("WSAStartup failed !/n");  
        return 1;  

    }  
	// 创建套接字  
    sockClient = socket(AF_INET,SOCK_DGRAM,0);  
    if(sockClient == INVALID_SOCKET)  
    {  
        printf("socket() failed, Error Code:%d/n",WSAGetLastError());  
        return 1;  
    }  

	// 设置服务器地址  
    servAddr.sin_family = AF_INET;  
    servAddr.sin_addr.S_un.S_addr = inet_addr(ip);  
    servAddr.sin_port = htons(port);
	return 0;
}

int SendParam(char * buff, unsigned int len)
{
	int nRst = 0;
	char rxBuff[64];
	// 向服务器发送数据  
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
		// 打印来自服务端发送来的数据  
		printf("result:%s\n", rxBuff); 
	}
  
	return RST_OK;
}

void Help()
{
	printf("workmode -- 工作模式（战斗模式、低截获）\n");
	printf("transmode -- 传输模式（代理、透传）\n");
	printf("mode -- 模式（定频、跳频）\n");
	printf("freq -- 频率设置\n");
	printf("speed -- 速率设置\n");
	printf("bw -- 带宽设置\n");
	printf("localip -- 本地IP\n");
	printf("localport -- 本地端口\n");
	printf("mac -- MAC地址\n");
	printf("remoteip -- 上位机IP\n");
	printf("remoteport -- 上位机端口\n");
	printf("netid -- 网络ID\n");
	printf("netsize -- 网络规模\n");
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
		printf(">>>请输入指令:");
		do {
			c = getchar();
			cmdLine[cmdLength++] = c;
		}while(c != '\n');

		if (cmdLine[0] == '\n'){
			//直接输入了回车
			continue;
		}

		//解析指令
		//最后的'\n'替换成空格以识别最后的参数
		cmdLine[cmdLength-1] = ' ';

		if (CheckParamValid(cmdLine) == false){
			printf("\nError:输入参数不合法\n");
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
