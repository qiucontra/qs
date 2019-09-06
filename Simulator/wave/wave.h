//#ifndef _WAVE_H_
//#define _WAVE_H_
#pragma once
#include "../option.h"
#include "../action/protocol.h"

#define WAVE_COUNT		3
#define WAVE_NAME_MAX	16//支持中文最多三个字符
#define WAVE_PARAM_MAX	64//支持最多16个英语字符，8个中文字符

enum
{
//user
	PARAM_WORKMODE = 0, //工作模式，战斗，低截获
	PARAM_TRANSMODE, //转发模式，透传，代理
	PARAM_MODE, //跳频，定频
	PARAM_FREQ, //频率
	PARAM_SPEED, //速率
	PARAM_BANDWIDTH, //带宽
	PARAM_IP, //本地IP
	PARAM_PORT, //本地端口
	PARAM_MAC, //上位机MAC
	PARAM_REMOTE_IP, //上位机IP
	PARAM_REMOTE_PORT, //上位机端口
	PARAM_NET_ID, //波形网络ID
	PARAM_NET_SIZE, //网络规模
	PARAM_RT_RES, //实时资源
//debug
	
	PARAM_MAX
};

#if defined PIXEL_256X128
static char ParamName[][WAVE_PARAM_MAX]={
	"工作模式","转发模式","模式","频率","速率","带宽","本地IP","本地端口","MAC",
	"上位机IP","上位机端口","网络ID","网络规模","实时资源"
};
#elif defined PIXEL_128X64
static char ParamName[][WAVE_PARAM_MAX]={
	"工作模式","转发模式","模式","频率","速率","带宽","本地IP","本地端口","MAC",
	"PC IP","PC端口","网络ID","网络规模","实时资源"
};
#endif

enum
{
	NET_P2P = 0,
	NET_ADHOC
};

//波形的类型
enum
{
	WAVE_NONE = 0,
	WAVE_WEAPON,
	WAVE_SQUAD,
	WAVE_ADHOC,
	WAVE_UNLOAD,
	WAVE_MAX
};

static char WaveName[][WAVE_PARAM_MAX] = {
	"None","武协","分队","自组网","卸载"
};


//波形的工作模式
enum
{
	WORKMODE_COMBAT = 0, //战斗模式
	WORKMODE_LP, //低截获模式
	WORKMODE_MAX
};

static char WaveWorkMode[][WAVE_PARAM_MAX]={
	"战斗","低截获"
};

//波形的转发模式======================================//
enum
{
	TRANS_AGENCY = 0, //代理模式
	TRANS_PASSTHROUGH, //透传模式
	TRANS_MAX
};
static char WaveTransMode[][WAVE_PARAM_MAX] = {
	"代理模式","透传模式"
};
//波形的模式======================================//
enum
{
	SEQ_UNHOPPING = 0, //定频
	SEQ_HOPPING, //跳频
	SEQ_MAX
};
static char WaveMode[][WAVE_PARAM_MAX] = {
	"定频","跳频"
};
//波形的速率======================================//
enum
{
	SPEED_10K = 0,
	SPEED_20K,
	SPEED_50K,
	SPEED_100K,
	SPEED_MAX
};
static char WaveSpeed[][WAVE_PARAM_MAX] = {
	"10Kbps","20Kbps","50Kbps","100Kbps"
};
//波形的带宽======================================//
enum
{
	BW_500K = 0,
	BW_1M,
	BW_2M,
	BW_5M,
	BW_10M,
	BW_MAX
};
static char WaveBandWidth[][WAVE_PARAM_MAX] = {
	"500KHz","1MHz","2MHz","5MHz","10MHz"
};
//频率的数量级======================================//
enum
{
	FREQ_UNIT_GHZ = 0,
	FREQ_UNIT_MHZ,
	FREQ_UNIT_KHZ,
	FREQ_UNIT_MAX
};
static char FreqUnitName[][WAVE_PARAM_MAX]={
	"GHz","MHz","KHz"
};
//波形参数对应的数值======================================//
typedef struct waveparam_t
{
	unsigned int type;
	char (* params)[WAVE_PARAM_MAX];
}WAVEPARAM_T;

static WAVEPARAM_T WaveParams[] = {
	{PARAM_WORKMODE, WaveWorkMode},
	{PARAM_TRANSMODE, WaveTransMode},
	{PARAM_MODE, WaveMode},
	{PARAM_FREQ, NULL},
	{PARAM_SPEED, WaveSpeed},
	{PARAM_BANDWIDTH, WaveBandWidth},
	{PARAM_IP, NULL},
	{PARAM_PORT, NULL},
	{PARAM_MAC, NULL},
	{PARAM_REMOTE_IP, NULL},
	{PARAM_REMOTE_PORT, NULL},
	{PARAM_NET_ID, NULL},
	{PARAM_NET_SIZE, NULL},
	{PARAM_RT_RES, NULL},
};
//===========================================================//

class Wave
{
public:
	Wave(unsigned int wavetype, unsigned int chl);
	~Wave();

public:
	char m_szName[WAVE_NAME_MAX];
	unsigned short m_nLocalIp[4]; //本地ip
	unsigned int m_nLocalPort; //本地端口
	unsigned short m_nMac[6]; //mac地址
	unsigned long m_nFreq; //频率
	unsigned int m_nSpeed; //速率
	unsigned int m_nType; 
	unsigned int m_nMode;
	unsigned int m_nWorkmode;
	unsigned int m_nBandwidth;
	unsigned int m_nTransmode;
	unsigned short m_nRemoteIp[4];
	unsigned int m_nRemotePort;
	unsigned short m_nNetId;
	unsigned short m_nNetSize;
	unsigned short m_nRtResource;

	unsigned int m_bSetting;

	Protocol * m_pProtocol;
public:
	int Init(unsigned int wavetype, unsigned int chl);
	int FreqToString(char * pszBuff, unsigned long nFreq);
	void IpToString(char * pszBuff, unsigned short nIp[]);
	void PortToString(char * pszBuff, unsigned int nPort);
	void MacToString(char * pszBuff, unsigned short nMac[]);
	void NetIdToString(char * pszBuff, unsigned short nNetId);
	void NetSizeToString(char * pszBuff, unsigned short nNetSize);
	void FreqToInt(char * pszBuff, unsigned long * nFreq);
	void IpToInt(char * pszBuff, unsigned short * pIp);
	void PortToInt(char * pszBuff, unsigned int * pPort);
	void MacToInt(char * pszBuff, unsigned short * pMac);
	void NetIdToInt(char * pszBuff, unsigned short * pNetId);
	void NetSizeToInt(char * pszBuff, unsigned short * pNetSize);

public:
	static char * GetWaveName(unsigned int nType){
		return WaveName[nType];
	};
	static char * GetWaveMode(unsigned int nMode){
		return WaveMode[nMode];
	};
	static char * GetParam(unsigned int nType, int nParam){
		return WaveParams[nType].params[nParam];
	};
	static char * GetParamName(unsigned int nType){
		return ParamName[nType];
	};
	static char * GetFreqUnitName(unsigned int nUnit){
		return FreqUnitName[nUnit];
	}

private:
	int InitWeaponWave();
	int InitSquadWave();
	int InitAdHocWave();
};
//#endif