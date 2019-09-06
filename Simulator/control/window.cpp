#include "stdafx.h"
#include "window.h"

#ifdef WIN32
#include "../resource.h"
#endif
#include "../SimulatorDlg.h"
//#endif
#include "../wave/wave.h"
#include "../control/channel.h"
#include "../control/paramset.h"
#include "../control/process.h"
#include "../control/select.h"
#include "../control/input.h"
#include "../control/optionbar.h"
#include "../control/titlebar.h"
#include "../control/waveselect.h"
#include "../action/waveload.h"

//add by qiushi 2018-09-18
Wnd::Wnd(WND_TYPE type)
{
	m_nType = type;
	m_pCtlLst = NULL;
	m_pFather = NULL;
	m_nCtlNum = 0;
	memset(m_tListener, 0, sizeof(LISTENER_T)*KEY_MAX);
}

Wnd::~Wnd()
{
	ClearControl();
}
//��ӿؼ�
int Wnd::AddControl(CTL_TYPE nCtlType, unsigned int id, void *pItem)
{
	CONTROL_T * tmp = (CONTROL_T *)calloc(m_nCtlNum+1, sizeof(CONTROL_T));
	CONTROL_T * cur = &tmp[m_nCtlNum];
	//���֮ǰ��ָ�벻Ϊ�գ���ʾԭ������Item����ԭ��Item����
	if (m_pCtlLst != NULL){
		memcpy(tmp, m_pCtlLst, sizeof(CONTROL_T)*m_nCtlNum); 
		free(m_pCtlLst);
	}

	cur->type = nCtlType;
	cur->id = id;
	cur->item = pItem;
	m_pCtlLst = tmp;
	m_nCtlNum ++;
	return true;
}
//��մ������еĿؼ�
void Wnd::ClearControl()
{
	for (unsigned int i=0; i<m_nCtlNum; i++){
		CONTROL_T * pCtl = &m_pCtlLst[i];
		switch(pCtl->type){
		case CTL_PROCESS:{
			MyProcess * item = (MyProcess *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_WAVESET:{
			ParamSet * item = (ParamSet *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_CHANNEL:{
			Channel * item = (Channel *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_SELECT:{
			MySelect * item = (MySelect *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_INPUT:{
			MyInput * item = (MyInput *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_WAVESELECT:{
			WaveSelect * item = (WaveSelect *)pCtl->item;
			DELETE_OBJ(item);
			}
			break;
		case CTL_TITLEBAR:
			//ֻ���������ڱ�ɾ����ʱ����ͷ�TitleBar�ؼ�
			if (m_nType == WND_MAIN){ 
				TitleBar * item = (TitleBar *)pCtl->item;
				DELETE_OBJ(item);
			}
			break;
		case CTL_OPTIONBAR:
			//ֻ���������ڱ�ɾ����ʱ����ͷ�OptionBar�ؼ�
			if (m_nType == WND_MAIN){ 
				OptionBar * item = (OptionBar *)pCtl->item;
				DELETE_OBJ(item);
			}
			break;
		default:
			break;
		}
	}
	FREE(m_pCtlLst);
}
//��Ӽ���
int Wnd::AddListener(unsigned int nLisType, int(* cb)(void *, unsigned int))
{
	if (nLisType >= KEY_MAX){
		printf("[%s]listener type is out of range<nLisType=%d>", nLisType);
		return false;
	}

	m_tListener[nLisType].keynum = nLisType;
	m_tListener[nLisType].callback = cb;
	return true;
}
//ͨ��ID��ȡ�ؼ�
void * Wnd::GetItemById(unsigned int nId)
{
	for (int i=0; i<m_nCtlNum; i++){
		if (m_pCtlLst[i].id == nId){
			return m_pCtlLst[i].item;
		}
	}
	return NULL;
}
//���ڲ���
void Wnd::Layout()
{
	for (unsigned int i=0; i<m_nCtlNum; i++){
		CONTROL_T * pCtl = &m_pCtlLst[i];
		switch (pCtl->type){
		case CTL_PROCESS:{
			MyProcess * p = (MyProcess *)pCtl->item;
			p->Draw();
			}
			break;
		case CTL_TITLEBAR:{
			TitleBar * p = (TitleBar *)pCtl->item;
			p->Draw();
			}
			break;
		case CTL_OPTIONBAR:{
			OptionBar * p = (OptionBar *)pCtl->item;
			p->Draw();
			}
			break;
		case CTL_CHANNEL:{
			Channel * p = (Channel *)pCtl->item;
			p->Draw();
			}
			break;
		case CTL_WAVESELECT:{
			WaveSelect * p = (WaveSelect *)pCtl->item;
			p->Draw();
			}
			break;
		case CTL_WAVESET:{
			ParamSet * p = (ParamSet *)pCtl->item;
			p->Draw();
		}
		break;
		case CTL_SELECT:{
			MySelect * p = (MySelect *)pCtl->item;
			p->Draw();
			}
			break;
		default:
			break;
		}
	}
}
//��Ϣ�����ͳһHandle����
int Wnd::Handle(void * pObj, unsigned int nKey)
{
	if (nKey >= KEY_MAX){
		return false;
	}

	LISTENER_T * pListener = &m_tListener[nKey];
	if (pListener->callback != NULL){
		pListener->callback(pObj, nKey);
	}

	return true;
}