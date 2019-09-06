//#ifndef _PROTOCOL_H_
//#define _PROTOCOL_H_
#pragma once
#include "sock.h"

class Protocol
{
public:
	Protocol(char * pszIp, unsigned int nPort);
	~Protocol();

	int SetWorkMode(unsigned int nWorkMode);
	int SetTransMode(unsigned int nTransMode);
	int SetSpeed(unsigned int nSpeed);
	int SetBandwidth(unsigned int nBandwidth);
	int SetFreq(unsigned int nFreq);
	int SetLocalIp(unsigned short ip[]);
	int SetLocalPort(unsigned int nPort);
	int SetRemoteIp(unsigned short ip[]);
	int SetRemotePort(unsigned int nPort);
	int SetMac(unsigned short mac[]);
	int SetNetId(unsigned short nNetId);
	int SetNetSize(unsigned short nNetSize);

private:
	Sock m_sock;

};

//#endif 