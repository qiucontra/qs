//#ifndef _WAVESLECT_H_
//#define _WAVESLECT_H_
#pragma once

typedef struct waveselect_t
{
	unsigned int type;
	unsigned int x;
	unsigned int y;
	unsigned int number;
	bool selected;
}WAVESELECT_T;

class WaveSelect
{
public:
	WaveSelect(unsigned int nChl);
	~WaveSelect();

public:
	void Switch(unsigned int nKey);
	WAVESELECT_T * GetCurWave(){
		return &m_tWaveSelect[m_nCurWave];
	};
	void Draw();

private:
	unsigned int m_nCurChl;
	unsigned int m_nCurWave;
	WAVESELECT_T m_tWaveSelect[4];
};
//#endif