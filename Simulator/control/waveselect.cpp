#include "stdafx.h"
#include "waveselect.h"
#include "../option.h"
#include "../mmi/display.h"
#include "../wave/wave.h"
#include "channel.h"

#if defined PIXEL_128X64
#define WAVESELECT_SX		10
#define WAVESELECT_DELTA_X	64
#define WAVESELECT_SY		18
#define WAVESELECT_DELTA_Y	24
#define WAVESELECT_W		52
#define WAVESELECT_H		20
#endif

//add by qiushi 2018-09-23
WaveSelect::WaveSelect(unsigned int nChl)
{
	m_nCurChl = nChl;
	m_nCurWave = 0;

#if defined PIXEL_256X128
	m_tWaveSelect[0].type = WAVE_WEAPON;
	m_tWaveSelect[0].x = CHANNEL_AREA_X + 56;
	m_tWaveSelect[0].y = TITLEBAR_AREA_H;
	m_tWaveSelect[0].selected = true;

	m_tWaveSelect[1].type = WAVE_SQUAD;
	m_tWaveSelect[1].x = CHANNEL_AREA_X + 156;
	m_tWaveSelect[1].y = TITLEBAR_AREA_H;
	m_tWaveSelect[1].selected = false;

	m_tWaveSelect[2].type = WAVE_ADHOC;
	m_tWaveSelect[2].x = CHANNEL_AREA_X + 56;
	m_tWaveSelect[2].y = TITLEBAR_AREA_H+CHANNEL_SIZE;
	m_tWaveSelect[2].selected = false;

	m_tWaveSelect[3].type = WAVE_UNLOAD;
	m_tWaveSelect[3].x = CHANNEL_AREA_X + 156;
	m_tWaveSelect[3].y = TITLEBAR_AREA_H+CHANNEL_SIZE;
	m_tWaveSelect[3].selected = false;
#elif defined PIXEL_128X64
	m_tWaveSelect[0].type = WAVE_WEAPON;
	m_tWaveSelect[0].x = WAVESELECT_SX;
	m_tWaveSelect[0].y = WAVESELECT_SY;
	m_tWaveSelect[0].selected = true;

	m_tWaveSelect[1].type = WAVE_SQUAD;
	m_tWaveSelect[1].x = WAVESELECT_SX+WAVESELECT_DELTA_X;
	m_tWaveSelect[1].y = WAVESELECT_SY;
	m_tWaveSelect[1].selected = false;

	m_tWaveSelect[2].type = WAVE_ADHOC;
	m_tWaveSelect[2].x = WAVESELECT_SX;
	m_tWaveSelect[2].y = WAVESELECT_SY+WAVESELECT_DELTA_Y;
	m_tWaveSelect[2].selected = false;

	m_tWaveSelect[3].type = WAVE_UNLOAD;
	m_tWaveSelect[3].x = WAVESELECT_SX+WAVESELECT_DELTA_X;
	m_tWaveSelect[3].y = WAVESELECT_SY+WAVESELECT_DELTA_Y;
	m_tWaveSelect[3].selected = false;
#endif
}

WaveSelect::~WaveSelect()
{
}

void WaveSelect::Switch(unsigned int nKey)
{
	switch (nKey){
		case KEY_UP:
			if (m_nCurWave == 2 || m_nCurWave == 3){
				m_nCurWave -= 2;
			}
			break;
		case KEY_DOWN:
			if (m_nCurWave == 0 || m_nCurWave == 1){
				m_nCurWave += 2;
			}
			break;
		case KEY_LEFT:
			if (m_nCurWave == 1 || m_nCurWave == 3){
				m_nCurWave --;
			}
			break;
		case KEY_RIGHT:
			if (m_nCurWave == 0 || m_nCurWave == 2){
				m_nCurWave ++;
			}
			break;
		default:
			break;
	}

	for (int i=0; i<4; i++){
		m_tWaveSelect[i].selected = false;
	}
	m_tWaveSelect[m_nCurWave].selected = true;
} 

void WaveSelect::Draw()
{
	char buff[64];
#if defined PIXEL_256X128
	Display::Clear(CHANNEL_AREA_X, CHANNEL_AREA_Y, CHANNEL_AREA_W, CHANNEL_AREA_H);
	Display::PrintString(Channel::GetChlName(m_nCurChl), CHL_SX, TITLEBAR_AREA_H+CHANNEL_SIZE*m_nCurChl+8, FONT_MID);
	for (int i=0; i<4; i++){
		Display::PrintString(Wave::GetWaveName(m_tWaveSelect[i].type), m_tWaveSelect[i].x+8, m_tWaveSelect[i].y+8, FONT_MID);
		if (m_tWaveSelect[i].selected == true){
			Display::Reverse(m_tWaveSelect[i].x, m_tWaveSelect[i].y, 100, CHANNEL_SIZE);
		}
	}
#elif defined PIXEL_128X64
	Display::Clear();
	SPRINTF(buff, "%s²¨ÐÎÑ¡Ôñ:", Channel::GetChlName(m_nCurChl));
	Display::PrintString(buff, 2, 2, FONT_SMALL);
	for (int i=0; i<4; i++){
		Display::PrintString(Wave::GetWaveName(m_tWaveSelect[i].type), m_tWaveSelect[i].x, m_tWaveSelect[i].y, FONT_MID);
		if (m_tWaveSelect[i].selected == true){
			Display::Reverse(m_tWaveSelect[i].x, m_tWaveSelect[i].y, WAVESELECT_W, WAVESELECT_H);
		}
	}
#endif
}