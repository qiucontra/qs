//#ifndef _WAVE_H_
//#define _WAVE_H_
#pragma once
#include "../option.h"
#include "../action/protocol.h"

#define WAVE_COUNT		3
#define WAVE_NAME_MAX	16//֧��������������ַ�
#define WAVE_PARAM_MAX	64//֧�����16��Ӣ���ַ���8�������ַ�

enum
{
//user
	PARAM_WORKMODE = 0, //����ģʽ��ս�����ͽػ�
	PARAM_TRANSMODE, //ת��ģʽ��͸��������
	PARAM_MODE, //��Ƶ����Ƶ
	PARAM_FREQ, //Ƶ��
	PARAM_SPEED, //����
	PARAM_BANDWIDTH, //����
	PARAM_IP, //����IP
	PARAM_PORT, //���ض˿�
	PARAM_MAC, //��λ��MAC
	PARAM_REMOTE_IP, //��λ��IP
	PARAM_REMOTE_PORT, //��λ���˿�
	PARAM_NET_ID, //��������ID
	PARAM_NET_SIZE, //�����ģ
	PARAM_RT_RES, //ʵʱ��Դ
//debug
	
	PARAM_MAX
};

#if defined PIXEL_256X128
static char ParamName[][WAVE_PARAM_MAX]={
	"����ģʽ","ת��ģʽ","ģʽ","Ƶ��","����","����","����IP","���ض˿�","MAC",
	"��λ��IP","��λ���˿�","����ID","�����ģ","ʵʱ��Դ"
};
#elif defined PIXEL_128X64
static char ParamName[][WAVE_PARAM_MAX]={
	"����ģʽ","ת��ģʽ","ģʽ","Ƶ��","����","����","����IP","���ض˿�","MAC",
	"PC IP","PC�˿�","����ID","�����ģ","ʵʱ��Դ"
};
#endif

enum
{
	NET_P2P = 0,
	NET_ADHOC
};

//���ε�����
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
	"None","��Э","�ֶ�","������","ж��"
};


//���εĹ���ģʽ
enum
{
	WORKMODE_COMBAT = 0, //ս��ģʽ
	WORKMODE_LP, //�ͽػ�ģʽ
	WORKMODE_MAX
};

static char WaveWorkMode[][WAVE_PARAM_MAX]={
	"ս��","�ͽػ�"
};

//���ε�ת��ģʽ======================================//
enum
{
	TRANS_AGENCY = 0, //����ģʽ
	TRANS_PASSTHROUGH, //͸��ģʽ
	TRANS_MAX
};
static char WaveTransMode[][WAVE_PARAM_MAX] = {
	"����ģʽ","͸��ģʽ"
};
//���ε�ģʽ======================================//
enum
{
	SEQ_UNHOPPING = 0, //��Ƶ
	SEQ_HOPPING, //��Ƶ
	SEQ_MAX
};
static char WaveMode[][WAVE_PARAM_MAX] = {
	"��Ƶ","��Ƶ"
};
//���ε�����======================================//
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
//���εĴ���======================================//
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
//Ƶ�ʵ�������======================================//
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
//���β�����Ӧ����ֵ======================================//
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
	unsigned short m_nLocalIp[4]; //����ip
	unsigned int m_nLocalPort; //���ض˿�
	unsigned short m_nMac[6]; //mac��ַ
	unsigned long m_nFreq; //Ƶ��
	unsigned int m_nSpeed; //����
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