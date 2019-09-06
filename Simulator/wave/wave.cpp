#include "stdafx.h"
#include "wave.h"
#include "../option.h"
#include "string.h"

Wave::Wave(unsigned int wavetype, unsigned int chl)
{
	char buffer[32] = {0};
	m_nType = wavetype;
	STRCPY(m_szName, Wave::GetWaveName(m_nType));

	m_pProtocol = new Protocol(LOCAL_IP, LOCAL_PORT);
	Init(wavetype, chl);
}

Wave::~Wave()
{
	delete m_pProtocol;
}

int Wave::InitWeaponWave()
{
	IpToInt("192.168.0.1", m_nLocalIp);
	m_nLocalPort = 8080;
	IpToInt("233.50.0.1", m_nRemoteIp);
	m_nRemotePort = 6800;
	MacToInt("AA:34:AB:45:CC:EF", m_nMac);
	m_nFreq = 500000000;
	m_nSpeed = SPEED_100K;
	m_nMode = SEQ_UNHOPPING;
	m_nWorkmode = WORKMODE_COMBAT;
	m_nBandwidth = BW_500K;
	m_nTransmode = TRANS_PASSTHROUGH;
	m_nNetId = 6;
	m_nNetSize = 16;
	m_nRtResource = 5;
	return 0;
}

int Wave::InitSquadWave()
{
	IpToInt("127.0.0.1", m_nLocalIp);
	m_nLocalPort = 8080;
	IpToInt("107.50.234.109", m_nRemoteIp);
	m_nRemotePort = 6789;
	m_nFreq = 700000000;
	m_nSpeed = SPEED_100K;
	m_nMode = SEQ_UNHOPPING;
	m_nWorkmode = WORKMODE_COMBAT;
	m_nBandwidth = BW_500K;
	m_nTransmode = TRANS_PASSTHROUGH;
	m_nNetId = 0;
	m_nNetSize = 8;
	m_nRtResource = 0;
	return 0;
}

int Wave::InitAdHocWave()
{
	IpToInt("192.168.233.11", m_nLocalIp);
	m_nLocalPort = 8080;
	IpToInt("107.50.234.109", m_nRemoteIp);
	m_nRemotePort = 6789;
	MacToInt("12:34:12:45:78:90", m_nMac);
	m_nFreq = 800000000;
	m_nSpeed = SPEED_100K;
	m_nMode = SEQ_UNHOPPING;
	m_nBandwidth = BW_500K;
	m_nTransmode = TRANS_PASSTHROUGH;
	m_nNetId = 11;
	m_nNetSize = 32;
	m_nRtResource = 0;
	return 0;
}

int Wave::Init(unsigned int wavetype, unsigned int chl)
{
	if (wavetype < WAVE_WEAPON || wavetype > WAVE_ADHOC){
		printf("[%s]wave type error<type=%d>\n", __FUNCTION__, wavetype);
		return -1;
	}
	else if (wavetype == WAVE_WEAPON){
		InitWeaponWave();
	}
	else if (wavetype == WAVE_SQUAD){
		InitSquadWave();
	}
	else if (wavetype == WAVE_ADHOC){
		InitAdHocWave();
	}
	return 0;
}

int Wave::FreqToString(char * pszBuff, unsigned long nFreq)
{
	char tmp[32];
	float f = (float)nFreq;
	unsigned int unit = FREQ_UNIT_KHZ;
	
	if (nFreq / (1000*1000) == 0){
		f /= 1000;
		SPRINTF(tmp, "%.3fKHZ\0", f);
		unit = FREQ_UNIT_KHZ;
	}
	else if (nFreq / (1000*1000*1000) == 0){
		f /= (1000*1000);
		SPRINTF(tmp, "%.3fMHZ\0", f);
		unit = FREQ_UNIT_MHZ;
	}
	else {
		f /= (1000*1000*1000);
		SPRINTF(tmp, "%.3fGHZ\0", f);
		unit = FREQ_UNIT_GHZ;
	}

	//strcpy_s有问题，不知原因？？
	memcpy(pszBuff, tmp, strlen(tmp)+1);
	return unit;
}

void Wave::IpToString(char * pszBuff, unsigned short nIp[])
{
	char tmp[32];
	SPRINTF(tmp, "%d.%d.%d.%d\0", nIp[0], nIp[1], nIp[2], nIp[3]);
	memcpy(pszBuff, tmp, strlen(tmp)+1);
}

void Wave::PortToString(char * pszBuff, unsigned int nPort)
{
	char tmp[32];
	SPRINTF(tmp, "%d\0", nPort);
	memcpy(pszBuff, tmp, strlen(tmp)+1);
}

void Wave::MacToString(char * pszBuff, unsigned short nMac[])
{
	char tmp[32];
	SPRINTF(tmp, "%x:%x:%x:%x:%x:%x\0", nMac[0], nMac[1], nMac[2], nMac[3], nMac[4], nMac[5]);
	Transfer::Strupr(tmp);
	memcpy(pszBuff, tmp, strlen(tmp)+1);
}

void Wave::NetIdToString(char * pszBuff, unsigned short nNetId)
{
	char tmp[32];
	SPRINTF(tmp, "%d\0", nNetId);
	memcpy(pszBuff, tmp, strlen(tmp)+1);
}

void Wave::NetSizeToString(char * pszBuff, unsigned short nNetSize)
{
	char tmp[32];
	SPRINTF(tmp, "%d\0", nNetSize);
	memcpy(pszBuff, tmp, strlen(tmp)+1);
}

void Wave::FreqToInt(char * pszBuff, unsigned long * nFreq)
{
	unsigned int i=0, j=0, m=0, n=0;
	char freq[4] = {0};

	memset(freq, 0, sizeof(char)*4);
	for (i=0; i<strlen(pszBuff); i++){
		char c = pszBuff[i];
		//如果没有'.'而直接发现非0~9的字符，则说明"30MHz"这种情况的输入
		if (c == '.' || c < '0' || c > '9'){
			m = atoi(freq);
			j = 0;
			break;
		}
		else {
			freq[j++] = c;
		}
	}

	//之后在找到'.'的时候，才需要解析小数点后面
	if (pszBuff[i] == '.'){
		for (i=i+1; i<strlen(pszBuff); i++){
			char c = pszBuff[i];
			if (c >= '0' && c<= '9'){
				freq[j++] = c;
			}
			else {
				n = atoi(freq);
				j = 0;
				break;
			}
		}
	}

	if (pszBuff[i] == 'K'){
		*nFreq = m*KHZ + n;
	}
	else if (pszBuff[i] == 'M'){
		*nFreq = m*MHZ + n*KHZ;
	}
	else if (pszBuff[i] == 'G'){
		*nFreq = m*GHZ + n*MHZ;
	}
}

void Wave::IpToInt(char * pszBuff, unsigned short * pIp)
{
	unsigned int i=0, j=0, m=0;
	char ip[4];

	memset(ip, 0, sizeof(char)*4);
	for (i=0; i<strlen(pszBuff); i++){
		char c = pszBuff[i];
		if (c == '.'){
			j = 0;
			pIp[m++] = atoi(ip);
			memset(ip, 0, sizeof(char)*4);
		}
		else {
			ip[j++] = c;
		}
	}

	pIp[m++] = atoi(ip);
	memset(ip, 0, sizeof(char)*4);
}

void Wave::PortToInt(char * pszBuff, unsigned int * pPort)
{
	*pPort = atoi(pszBuff);
}

void Wave::MacToInt(char * pszBuff, unsigned short * pMac)
{
	char mac[3] = {0};
	unsigned int i=0, j=0, m=0;
	
	memset(mac, 0, sizeof(char)*3);
	for (i=0; i<strlen(pszBuff); i++){
		char c = pszBuff[i];
		if (c == ':'){
			j = 0;
			pMac[m++] = Transfer::HexToInt(mac);
			memset(mac, 0, sizeof(char)*3);
		}
		else {
			mac[j++]  = c;
		}
	}

	pMac[m] = Transfer::HexToInt(mac);
}

void Wave::NetIdToInt(char * pszBuff, unsigned short * pNetId)
{
	*pNetId = atoi(pszBuff);
}

void Wave::NetSizeToInt(char * pszBuff, unsigned short * pNetSize)
{
	*pNetSize = atoi(pszBuff);
}

