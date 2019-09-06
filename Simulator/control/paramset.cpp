#include "stdafx.h"
#include "ParamSet.h"
#include "../option.h"
#include "../mmi/display.h"
#include "paraminput.h"

#if defined PIXEL_256X128
#define CONTROL_SX				96
#define CONTROL_HEIGHT			20
#define PARAM_SX				100
#elif defined PIXEL_128X64
#define CONTROL_SX				56
#define CONTROL_HEIGHT			15
#define PARAM_SX				48
#endif

ParamSet::ParamSet(Wave * pWave)
{
	m_pParamCur = m_pParamStart = m_pParamEnd = m_pParam = NULL;
	m_bSelected = false;
	m_nParamCnt = 0;
	m_pWave = pWave;
}

ParamSet::~ParamSet()
{
	if (m_pParam != NULL){
		//首先释放空间
		for (unsigned int i=0; i<m_nParamCnt; i++){
			PARAM_T * param = &m_pParam[i];
			if (param->mode == PARAM_MODE_SELECT){
				MySelect * p = (MySelect *)param->control;
				DELETE_OBJ(p);
			}
			else if (param->mode == PARAM_MODE_INPUT){
				// todo ....
				ParamInput * p = (ParamInput *)param->control;
				DELETE_OBJ(p);
			}
		}

		FREE(m_pParam);
		m_pParam = NULL;
	}
}

int ParamSet::Switch(unsigned int key)
{
	int nRst = false;
	if (key == KEY_UP){
		while(m_pParamCur != m_pParam){
			nRst = true;
			m_pParamCur --;
			if (m_pParamCur->visible == true){
				break;
			}
		}
		if (m_bAutoScroll == true && m_pParamCur->num < m_pParamStart->num){
			m_pParamEnd = m_pParamStart = m_pParamCur;
			for (int i=0; i<(MAX_PARAM_CNT_ONEPAGE-1); i++){
				while (m_pParamEnd != &m_pParam[m_nParamCnt-1]){
					m_pParamEnd ++;
					if (m_pParamEnd->visible == true){
						break;
					}
				}
			}
		}
	}
	else if (key = KEY_DOWN){
		while(m_pParamCur != &m_pParam[m_nParamCnt-1]){
			nRst = true;
			m_pParamCur ++;
			if (m_pParamCur->visible == true){
				break;
			}
		}
		if (m_bAutoScroll == true && m_pParamCur->num > m_pParamEnd->num){
			m_pParamStart = m_pParamEnd = m_pParamCur;
			for (int i=0; i<(MAX_PARAM_CNT_ONEPAGE-1); i++){
				while (m_pParamStart != m_pParam){
					m_pParamStart --;
					if (m_pParamStart->visible == true){
						break;
					}
				}
			}
		}
	}
	else {
		//handle err...
	}
	return nRst;
}

void ParamSet::Draw(void)
{
	if (m_pParam != NULL){
		unsigned int i = 0;
		for (PARAM_T * p=m_pParamStart; p<=m_pParamEnd; p++){
			if (p->visible == false){
				continue;
			}

			Display::PrintString(Wave::GetParamName(p->type), 2, i*CONTROL_HEIGHT+4, FONT_SMALL);
#ifdef PIXEL_256X128
			//如果是MAC参数，需要显示当前输入是ABC还是123
			if (p->type == PARAM_MAC){
				ParamInput * item = (ParamInput *)p->control;
				if (item->isShift()){
					Display::PrintString("[ABC]", 40, i*CONTROL_HEIGHT+4, FONT_MINI);
				}
				else {
					Display::PrintString("[123]", 40, i*CONTROL_HEIGHT+4, FONT_MINI);
				}
			}
#endif
			Display::Clear((CONTROL_SX+4), i*CONTROL_HEIGHT+4, SCREEN_WIDTH-(CONTROL_SX+4), CONTROL_HEIGHT);
			if (p->mode == PARAM_MODE_SELECT){
				MySelect * sel = (MySelect *)p->control;
				sel->Move(CONTROL_SX, i*CONTROL_HEIGHT+4);
				sel->Draw();
			}
			else if (p->mode == PARAM_MODE_INPUT){
				ParamInput * input = (ParamInput *)p->control;
				input->Move(CONTROL_SX, i*CONTROL_HEIGHT+4);
				input->Draw();
			}

			//当前选择的参数，不是点击ENTER处于设置状态下
			if (m_pParamCur == p){
				Display::Reverse(0, i*CONTROL_HEIGHT+4, CONTROL_SX-4, CONTROL_HEIGHT);
			}
			//如果在选中设置的状态下，反转参数内容，反之反转参数名称
			if (m_pParamCur == p && m_bSelected == true){
				Display::Reverse(CONTROL_SX, i*CONTROL_HEIGHT+4, SCREEN_WIDTH-CONTROL_SX, CONTROL_HEIGHT);
				Display::Reverse(0, i*CONTROL_HEIGHT+4, CONTROL_SX-4, CONTROL_HEIGHT);
			}

			i++;
		}
	}
}

void * ParamSet::AddControl(unsigned int mode)
{
	if (mode == PARAM_MODE_SELECT){
		//参数为选择模型,使用MySelect控件
		MySelect * sel = new MySelect(CONTROL_SX, m_nParamCnt*20+4, SCREEN_WIDTH-CONTROL_SX, CONTROL_HEIGHT, FONT_SMALL);
		return (void *)sel;
	}
	else if (mode == PARAM_MODE_INPUT){
		//参数为输入模型，使用ParamInput控件
		ParamInput * input = new ParamInput(CONTROL_SX, m_nParamCnt*20+4, SCREEN_WIDTH-CONTROL_SX, CONTROL_HEIGHT, FONT_SMALL);
		return (void *)input;
	}

	return NULL;
}

int ParamSet::AddParam(unsigned int type, unsigned int mode, int (* ctl)(void *, unsigned int))
{
	if (type >= PARAM_MAX || mode >= PARAM_MODE_MAX){
		return -1;
	}

	PARAM_T * tmp = (PARAM_T *)calloc(m_nParamCnt+1, sizeof(PARAM_T));
	PARAM_T * cur = &tmp[m_nParamCnt];

	if (m_pParam != NULL){
		memcpy(tmp, m_pParam, sizeof(PARAM_T)*m_nParamCnt); 
		free(m_pParam);
	}

	cur->num = m_nParamCnt;
	cur->type = type;
	cur->mode = mode;
	STRCPY(cur->name, Wave::GetParamName(cur->type));
	cur->control = AddControl(mode);
	cur->ctl = ctl;
	cur->visible = true;

	m_pParam = tmp;
	m_nParamCnt ++;
	//添加过一个参数就将当前参数指向第一个
	m_pParamStart = m_pParamCur = &m_pParam[0];
	if (m_nParamCnt > MAX_PARAM_CNT_ONEPAGE){
		m_bAutoScroll = true;
	}
	else {
		m_pParamEnd = cur;
	}

	return (m_nParamCnt-1);
}

int ParamSet::AddParamSelectItem(unsigned int nNumber, unsigned int nValue, char * pszName)
{
	if (nNumber >= m_nParamCnt){
		printf("[%s]num error<num=%d>\n", __FUNCTION__, nNumber);
		return false;
	}
	
	PARAM_T * param = &m_pParam[nNumber];
	if (param->mode != PARAM_MODE_SELECT || param->control == NULL){
		printf("[%s]control error<mode=%d, control ptr=%x>\n", __FUNCTION__, nNumber, param->control);
		return false;
	}

	MySelect * sel = (MySelect *)param->control;
	sel->SetItem(nValue, pszName);
	return true;
}

int ParamSet::SetParamValue(unsigned int nNumber, unsigned int nValue)
{
	if (nNumber >= m_nParamCnt){
		printf("[%s]num error<num=%d>\n", __FUNCTION__, nNumber);
		return false;
	}

	PARAM_T * param = &m_pParam[nNumber];
	if (param->mode != PARAM_MODE_SELECT || param->control == NULL){
		printf("[%s]control error<mode=%d, control ptr=%x>\n", __FUNCTION__, nNumber, param->control);
		return false;
	}

	MySelect * sel = (MySelect *)param->control;
	sel->SetDefault(nValue);
	return true;
}

int ParamSet::SetInput(unsigned int nNumber, unsigned int nInputType, char * pValue)
{
	if (nNumber >= m_nParamCnt){
		printf("[%s]num error<num=%d>\n", __FUNCTION__, nNumber);
		return false;
	}

	PARAM_T * param = &m_pParam[nNumber];
	if (param->mode != PARAM_MODE_INPUT || param->control == NULL){
		printf("[%s]control error<mode=%d, control ptr=%x>\n", __FUNCTION__, nNumber, param->control);
		return false;
	}

	ParamInput * input = (ParamInput *)param->control;
	input->SetInputType(nInputType);
	input->SetValue(pValue);
	return true;
}

int ParamSet::SetParamStartEnd(unsigned int nNumberStart, unsigned int nNumberEnd)
{
	if (nNumberEnd < m_nParamCnt && nNumberEnd > nNumberStart){
		m_pParamStart = &m_pParam[nNumberStart];
		m_pParamEnd = &m_pParam[nNumberEnd];
		return true;
	}
	return false;
};

int ParamSet::SetVisible(unsigned int num, bool bVisible)
{
	if (num >= m_nParamCnt){
		printf("[%s]num is large than m_nParamCnt<num=%d, m_nParamCnt=%d>", num, m_nParamCnt);
		return false;
	}

	m_pParam[num].visible = bVisible;
	return true;
}

