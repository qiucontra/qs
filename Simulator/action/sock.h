//#ifndef _SOCK_H_
//#define _SOCK_H_
#pragma once

#include <WINSOCK2.H>  
#include <Windows.h>  
#pragma comment(lib,"WS2_32.lib")  

class Sock
{
public:
	Sock::Sock();
	Sock::~Sock();

	int ConnectServer(char * pszIp, unsigned int nPort);
	int SendParam(char * pBuff, unsigned int nLen);
	void  Close(){
		if (m_sockClient != INVALID_SOCKET){
			closesocket(m_sockClient);  
		}
	};

private:
	SOCKET m_sockClient;
	SOCKADDR_IN m_addrClient;
};


//#endif