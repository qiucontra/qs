#include "stdafx.h"
#include "protocol.h"
#include "../option.h"

//#define _USE_UDP

Protocol::Protocol(char * pszIp, unsigned int nPort)
{
	m_sock.ConnectServer(pszIp, nPort);
}

Protocol::~Protocol()
{
	m_sock.Close();
}

int Protocol::SetWorkMode(unsigned int nWorkMode)
{
	char buff[64];
	SPRINTF(buff, "workmode %d\0", nWorkMode);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetTransMode(unsigned int nTransMode)
{
	char buff[64];
	SPRINTF(buff, "transmode %d\0", nTransMode);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetSpeed(unsigned int nSpeed)
{
	char buff[64];
	SPRINTF(buff, "speed %d\0", nSpeed);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetBandwidth(unsigned int nBandwidth)
{
	char buff[64];
	SPRINTF(buff, "bw %d\0", nBandwidth);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetFreq(unsigned int nFreq)
{
	char buff[64];
	SPRINTF(buff, "freq %d\0", nFreq);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetLocalIp(unsigned short ip[])
{
	char buff[64];
	SPRINTF(buff, "localip %d %d %d %d\0", ip[0], ip[1], ip[2], ip[3]);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetLocalPort(unsigned int nPort)
{
	char buff[64];
	SPRINTF(buff, "localport %d\0", nPort);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetRemoteIp(unsigned short ip[])
{
	char buff[64];
	SPRINTF(buff, "remoteip %d %d %d %d\0", ip[0], ip[1], ip[2], ip[3]);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetRemotePort(unsigned int nPort)
{
	char buff[64];
	SPRINTF(buff, "remoteport %d\0", nPort);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetMac(unsigned short mac[])
{
	char buff[64];
	SPRINTF(buff, "mac %x %x %x %x %x %x\0", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetNetId(unsigned short nNetId)
{
	char buff[64];
	SPRINTF(buff, "netid %d\0", nNetId);
	return m_sock.SendParam(buff, strlen(buff));
}

int Protocol::SetNetSize(unsigned short nNetSize)
{
	char buff[64];
	SPRINTF(buff, "netsize %d\0", nNetSize);
	return m_sock.SendParam(buff, strlen(buff));
}



