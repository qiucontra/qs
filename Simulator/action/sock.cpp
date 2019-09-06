#include "stdafx.h"
#include <stdio.h>
#include "sock.h"
#include "../option.h"

#define RST_OK				(0)
#define RST_PARAM_ERROR		(-1)
#define RST_CMD_INVALID		(-2)
#define RST_EXIT			(1)
#define RST_HELP			(2)

Sock::Sock()
{
	m_sockClient = INVALID_SOCKET;
}

Sock::~Sock()
{
	
}

int Sock::ConnectServer(char * pszIp, unsigned int nPort)
{
	WSADATA wsd;    
	// 初始化套接字动态库  
    if(WSAStartup(MAKEWORD(2,2),&wsd) != 0)  
    {  
        printf("WSAStartup failed !/n");  
        return false;  

    }  
	// 创建套接字  
    m_sockClient = socket(AF_INET,SOCK_DGRAM,0);  
    if(m_sockClient == INVALID_SOCKET)  
    {  
        printf("socket() failed, Error Code:%d/n",WSAGetLastError());  
        return false;  
    }  

	// 设置服务器地址  
    m_addrClient.sin_family = AF_INET;  
	m_addrClient.sin_addr.S_un.S_addr = inet_addr(pszIp);  
	m_addrClient.sin_port = htons(nPort);
	return true;
}

int Sock::SendParam(char * pszBuff, unsigned int nLen)
{
	int nRst = 0;
	char rxBuff[64];
	// 向服务器发送数据  
    int nServAddLen = sizeof(m_addrClient);  
	if(sendto(m_sockClient, pszBuff, nLen, 0, (sockaddr *)&m_addrClient, nServAddLen) == SOCKET_ERROR){  
        printf("recvfrom() failed:%d\n",WSAGetLastError());  
        closesocket(m_sockClient);  
        WSACleanup();  
        return false;  
    } 
	memset(rxBuff, 0, sizeof(char)*64);
	nRst = recvfrom(m_sockClient, rxBuff, 64, 0, (sockaddr *)&m_addrClient, &nServAddLen);  
    if(SOCKET_ERROR == nRst)     
    {     
        printf("recvfrom failed !\n");     
        closesocket(m_sockClient);     
        WSACleanup();     
        return false;     
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

