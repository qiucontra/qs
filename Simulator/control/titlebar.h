//#ifndef _TITLEBAR_H_
//#define _TITLEBAR_H_
#pragma once

enum
{
	BATTERY_0 = 0,
	BATTERY_1,
	BATTERY_2,
	BATTERY_3,
	BATTERY_MAX
};

enum
{
	RSSI_0 = 0,
	RSSI_1,
	RSSI_2,
	RSSI_3,
	RSSI_4,
	RSSI_MAX
};

class TitleBar
{
public:
	TitleBar();
	~TitleBar();

public:
	//设置信号强度
	int SetSignal(unsigned int nChl, unsigned int nRssi);
	//设置时间
	int SetTime(unsigned int nHour, unsigned int nMinute);
	//设置电池容量
	int SetBattery(unsigned int nBattery);
	void Draw(void);

private:
	unsigned int m_nBattery;
	unsigned int m_nRssi[2];
	unsigned int m_nHour;
	unsigned int m_nMinute;
};
//#endif