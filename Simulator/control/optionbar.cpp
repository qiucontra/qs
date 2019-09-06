#include "stdafx.h"
#include "optionbar.h"
#include "../option.h"

OptionBar::OptionBar(unsigned int nPwr, unsigned int nChl, unsigned int nVol)
{
	
#if defined PIXEL_256X128
	int y = OPTIONBAR_SY + 4;
	int width = 60;
#elif defined PIXEL_128X64
	int y = OPTIONBAR_SY;
	int width = 30;
#endif

	m_pPwr = new MySelect(OPTION_PWR_SX, y, width, SCREEN_HEIGHT-y, FONT_SMALL);
	m_pPwr->SetItem(PWR_SMALL, "小功率");
	m_pPwr->SetItem(PWR_MID, "中功率");
	m_pPwr->SetItem(PWR_LARGE, "大功率");

	m_pChl = new MySelect(OPTION_CHL_SX, y, width, SCREEN_HEIGHT-y, FONT_SMALL);
	m_pChl->SetItem(CHL_1, "通道1");
	m_pChl->SetItem(CHL_2, "通道2");

	m_pVol = new MySelect(OPTION_VOL_SX, y, width, SCREEN_HEIGHT-y, FONT_SMALL);
	m_pVol->SetItem(VOL_0, "静音");
	m_pVol->SetItem(VOL_1, "音量1");
	m_pVol->SetItem(VOL_2, "音量2");
	m_pVol->SetItem(VOL_3, "音量3");
}

OptionBar::~OptionBar()
{
	DELETE_OBJ(m_pPwr);
	DELETE_OBJ(m_pChl);
	DELETE_OBJ(m_pVol);
}
//功能条中的音量，功率等控制接口
void OptionBar::Control(OPTION_CTL eCtlType, unsigned int nKey)
{
	switch(eCtlType){
		case OPTION_CTL_PWR:
			if (nKey == KEY_2){
				m_pPwr->SelectItem(SELECT_UP);
			}
			else if (nKey == KEY_7){
				m_pPwr->SelectItem(SELECT_DOWN);
			}
			break;
		case OPTION_CTL_CHL:
			if (nKey == KEY_3){
				m_pChl->SelectItem(SELECT_UP);
			}
			else if (nKey == KEY_8){
				m_pChl->SelectItem(SELECT_DOWN);
			}
			break;
		case OPTION_CTL_VOL:
			if (nKey == KEY_4){
				m_pVol->SelectItem(SELECT_UP);
			}
			else if (nKey == KEY_9){
				m_pVol->SelectItem(SELECT_DOWN);
			}
			break;
		default:
			printf("[%s]ctl is error<ctl=%d>", __FUNCTION__, eCtlType);
			break;
	}
}

void OptionBar::Draw(void)
{
	m_pPwr->Draw();
	m_pChl->Draw();
	m_pVol->Draw();
}