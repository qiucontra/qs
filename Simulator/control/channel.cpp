#include "stdafx.h"
#include "../option.h"
#include "channel.h"
#include "../mmi/display.h"

//modify by qiushi 2018-09-21
Channel::Channel(unsigned int chl)
{
	m_nChl = chl;
	m_pWave = NULL;
	m_pParamCtl = NULL;
	m_bSelected = false;
	SPRINTF(m_szChl,Channel::GetChlName(chl));
}

Channel::~Channel()
{
	DELETE_OBJ(m_pParamCtl);
	DELETE_OBJ(m_pWave);
}
#if defined PIXEL_256X128
int Channel::Draw()
{
	unsigned int y = TITLEBAR_AREA_H + CHANNEL_SIZE*m_nChl;

	if (m_nChl > CHL_MAX){
		printf("[%s]channel error<m_nChl=%d>", m_nChl);
		return false;
	}

	Display::Clear(0, y, CHL_WIDTH, CHL_HEIGHT);
	Display::PrintString(m_szChl, CHL_SX, y+CHL_WAVENAME_SY, FONT_MID);
	if (m_pWave == NULL){
		Display::PrintString("None", CHL_WAVENAME_SX, y+CHL_WAVENAME_SY, FONT_MID);
	}
	else{
		Display::PrintString(m_pWave->m_szName, CHL_WAVENAME_SX, y+CHL_WAVENAME_SY, FONT_MID);
		if (m_pParamCtl != NULL){
			m_pParamCtl->Draw();
		}
	}
	
	if (m_bSelected == true){
		Display::Reverse(0, y, CHL_WIDTH, CHL_HEIGHT);
	}

	return true;
}
#elif defined PIXEL_128X64
int Channel::Draw()
{
	unsigned int y = TITLEBAR_AREA_H+8;

	if (m_nChl > CHL_MAX){
		printf("[%s]channel error<m_nChl=%d>", m_nChl);
		return false;
	}

	if (m_bSelected == false){
		return true;
	}

	Display::Clear(0, y, CHL_WIDTH, CHL_HEIGHT);
	
	Display::PrintString(m_szChl, CHL_SX, y, FONT_MID);
	if (m_pWave == NULL){
		Display::PrintString("None", CHL_WAVENAME_SX, y, FONT_MID);
	}
	else{
		Display::PrintString(m_pWave->m_szName, CHL_WAVENAME_SX, y, FONT_MID);
		if (m_pParamCtl != NULL){
			//m_pParamCtl->Draw();
		}
	}
	return true;
}
#endif

void Channel::SwitchParam(unsigned int nKey)
{
	m_pParamCtl->SelectItem(nKey - KEY_LEFT);
	m_pParamCtl->Draw();
}

int Channel::InitWaveParam()
{
	char buff[64] = {0};
#if defined PIXEL_256X128
	unsigned int y = TITLEBAR_AREA_H + CHANNEL_SIZE*m_nChl + CHL_PARAM_SY;
	unsigned int x = CHL_PARAM_SX;
	unsigned int w = SCREEN_WIDTH-CHL_PARAM_SX;
	unsigned int h = CHL_PARAM_HEIGHT;
#elif defined PIXEL_128X64
	unsigned int y = TITLEBAR_AREA_H + CHL_PARAM_SY;
	unsigned int x = 70;
	unsigned int w = SCREEN_WIDTH - x;
	unsigned int h = 28;
#endif

	if (m_pWave == NULL){
		printf("[%s]m_pWave is NULL");
		return false;
	}
	else if (m_pWave->m_nType >= WAVE_UNLOAD){
		printf("[%s]wave type error<m_nType=%d>", m_pWave->m_nType);
		return false;
	}

	//如果参数控制控件已经存在的话，说明是在该通道再次加载其他波形
	DELETE_OBJ(m_pParamCtl);
	
	m_pParamCtl = new MySelect(x, y, w, h, FONT_SMALL);
	if (m_pWave->m_nType != WAVE_ADHOC){
		//工作模式
		m_pParamCtl->SetItem(0, Wave::GetParam(PARAM_WORKMODE, m_pWave->m_nWorkmode));
	}
	//转发模式
	m_pParamCtl->SetItem(0, Wave::GetParam(PARAM_TRANSMODE, m_pWave->m_nTransmode));
	//频率
	m_pWave->FreqToString(buff, m_pWave->m_nFreq);
	m_pParamCtl->SetItem(0, buff);
	//速率
	SPRINTF(buff, "速率 %s", Wave::GetParam(PARAM_SPEED, m_pWave->m_nSpeed));
	m_pParamCtl->SetItem(0, buff);
	//带宽
	SPRINTF(buff, "带宽 %s", Wave::GetParam(PARAM_BANDWIDTH, m_pWave->m_nBandwidth));
	m_pParamCtl->SetItem(0, buff);
	//本地IP
	m_pWave->IpToString(buff, m_pWave->m_nLocalIp);
	m_pParamCtl->SetItem(0, buff);
	//本地端口
	SPRINTF(buff, "本地端口 %d", m_pWave->m_nLocalPort);
	m_pParamCtl->SetItem(0, buff);
	//上位机IP
	m_pWave->IpToString(buff, m_pWave->m_nRemoteIp);
	m_pParamCtl->SetItem(0, buff);
	//上位机端口
	SPRINTF(buff, "上位机端口 %d", m_pWave->m_nRemotePort);
	m_pParamCtl->SetItem(0, buff);
	//网络ID
	SPRINTF(buff, "网络ID %d", m_pWave->m_nNetId);
	m_pParamCtl->SetItem(0, buff);
	//网络规模
	SPRINTF(buff, "网络规模 %d", m_pWave->m_nNetSize);
	m_pParamCtl->SetItem(0, buff);
	//实时资源
	if (m_pWave->m_nType == WAVE_WEAPON){
		SPRINTF(buff, "实时资源 %d", m_pWave->m_nRtResource);
		m_pParamCtl->SetItem(0, buff);
	}

	return true;
}
