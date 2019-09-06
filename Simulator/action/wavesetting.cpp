#include "stdafx.h"
#include "wavesetting.h"
#include "../RadioStation.h"
#include "../SimulatorDlg.h"

#include "../control/tooltip.h"
#include "../control/paramset.h"
#include "../control/select.h"
#include "../control/paraminput.h"

#define ID_CTL_PARAMSET		0
//���ò���
ParamSet * WaveSetting::SetWave(Wave * pWave)
{
	int num = 0;
	char buff[32] = {0};
	ParamSet * paramset = new ParamSet(pWave);

	//����ģʽ����
	if (pWave->m_nType == WAVE_SQUAD){
		num = paramset->AddParam(PARAM_WORKMODE, PARAM_MODE_SELECT, WaveSetting::HandleParamSelectCtl);
		paramset->AddParamSelectItem(num, WORKMODE_COMBAT, Wave::GetParam(PARAM_WORKMODE, WORKMODE_COMBAT));
		paramset->AddParamSelectItem(num, WORKMODE_LP, Wave::GetParam(PARAM_WORKMODE, WORKMODE_LP));
		paramset->SetParamValue(num, pWave->m_nWorkmode);
	}
	//ת��ģʽ
	num = paramset->AddParam(PARAM_TRANSMODE, PARAM_MODE_SELECT, WaveSetting::HandleParamSelectCtl);
	paramset->AddParamSelectItem(num, TRANS_AGENCY, Wave::GetParam(PARAM_TRANSMODE, TRANS_AGENCY));
	paramset->AddParamSelectItem(num, TRANS_PASSTHROUGH, Wave::GetParam(PARAM_TRANSMODE, TRANS_PASSTHROUGH));
	paramset->SetParamValue(num, pWave->m_nTransmode);
	//Ƶ��
	num = paramset->AddParam(PARAM_FREQ, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->FreqToString(buff, pWave->m_nFreq);
	paramset->SetInput(num, PARAMINPUT_FREQ, buff);
	//����
	num = paramset->AddParam(PARAM_SPEED, PARAM_MODE_SELECT, WaveSetting::HandleParamSelectCtl);
	if (pWave->m_nType == WAVE_WEAPON){
		paramset->AddParamSelectItem(num, SPEED_10K, Wave::GetParam(PARAM_SPEED, SPEED_10K));
		paramset->AddParamSelectItem(num, SPEED_50K, Wave::GetParam(PARAM_SPEED, SPEED_50K));
		paramset->AddParamSelectItem(num, SPEED_100K, Wave::GetParam(PARAM_SPEED, SPEED_100K));
	}
	else if (pWave->m_nType == WAVE_SQUAD){
		paramset->AddParamSelectItem(num, SPEED_10K, Wave::GetParam(PARAM_SPEED, SPEED_10K));
		paramset->AddParamSelectItem(num, SPEED_20K, Wave::GetParam(PARAM_SPEED, SPEED_20K));
		paramset->AddParamSelectItem(num, SPEED_50K, Wave::GetParam(PARAM_SPEED, SPEED_50K));
	}
	else if (pWave->m_nType == WAVE_ADHOC){
		paramset->AddParamSelectItem(num, SPEED_20K, Wave::GetParam(PARAM_SPEED, SPEED_20K));
		paramset->AddParamSelectItem(num, SPEED_100K, Wave::GetParam(PARAM_SPEED, SPEED_100K));
	}
	paramset->SetParamValue(num, pWave->m_nSpeed);
	//����
	num = paramset->AddParam(PARAM_BANDWIDTH, PARAM_MODE_SELECT, WaveSetting::HandleParamSelectCtl);
	if (pWave->m_nType == WAVE_WEAPON){
		paramset->AddParamSelectItem(num, BW_500K, Wave::GetParam(PARAM_BANDWIDTH, BW_500K));
		paramset->AddParamSelectItem(num, BW_2M, Wave::GetParam(PARAM_BANDWIDTH, BW_2M));
		paramset->AddParamSelectItem(num, BW_10M, Wave::GetParam(PARAM_BANDWIDTH, BW_10M));
	}
	else if (pWave->m_nType == WAVE_SQUAD){
		paramset->AddParamSelectItem(num, BW_1M, Wave::GetParam(PARAM_BANDWIDTH, BW_1M));
		paramset->AddParamSelectItem(num, BW_2M, Wave::GetParam(PARAM_BANDWIDTH, BW_2M));
		paramset->AddParamSelectItem(num, BW_5M, Wave::GetParam(PARAM_BANDWIDTH, BW_5M));
	}
	else if (pWave->m_nType == WAVE_ADHOC){
		paramset->AddParamSelectItem(num, BW_1M, Wave::GetParam(PARAM_BANDWIDTH, BW_1M));
		paramset->AddParamSelectItem(num, BW_2M, Wave::GetParam(PARAM_BANDWIDTH, BW_2M));
		paramset->AddParamSelectItem(num, BW_5M, Wave::GetParam(PARAM_BANDWIDTH, BW_5M));
		paramset->AddParamSelectItem(num, BW_10M, Wave::GetParam(PARAM_BANDWIDTH, BW_10M));
	}
	paramset->SetParamValue(num, pWave->m_nBandwidth);
	//����IP
	num = paramset->AddParam(PARAM_IP, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->IpToString(buff, pWave->m_nLocalIp);
	paramset->SetInput(num, PARAMINPUT_IP, buff);
	//���ض˿�
	num = paramset->AddParam(PARAM_PORT, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->PortToString(buff, pWave->m_nLocalPort);
	paramset->SetInput(num, PARAMINPUT_PORT, buff);
#ifdef PIXEL_256X128
	//MAC
	num = paramset->AddParam(PARAM_MAC, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->MacToString(buff, pWave->m_nMac);
	paramset->SetInput(num, PARAMINPUT_MAC, buff);
	if (pWave->m_nTransmode == TRANS_AGENCY){
		paramset->SetVisible(num, false);
	}
#elif defined PIXEL_128X64
	num = paramset->AddParam(PARAM_MAC, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	paramset->SetInput(num, PARAMINPUT_MAC, "����");
	if (pWave->m_nTransmode == TRANS_AGENCY){
		paramset->SetVisible(num, false);
	}
#endif
	//��λ��IP
	num = paramset->AddParam(PARAM_REMOTE_IP, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->IpToString(buff, pWave->m_nRemoteIp);
	paramset->SetInput(num, PARAMINPUT_IP, buff);
	//��λ���˿�
	num = paramset->AddParam(PARAM_REMOTE_PORT, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->PortToString(buff, pWave->m_nRemotePort);
	paramset->SetInput(num, PARAMINPUT_PORT, buff);
	//����ID
	num = paramset->AddParam(PARAM_NET_ID, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->NetIdToString(buff, pWave->m_nNetId);
	paramset->SetInput(num, PARAMINPUT_NETID, buff);
	//�����ģ
	num = paramset->AddParam(PARAM_NET_SIZE, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
	pWave->NetSizeToString(buff, pWave->m_nNetSize);
	paramset->SetInput(num, PARAMINPUT_NETSIZE, buff);
	//ʵʱ��Դ
	if (pWave->m_nType == WAVE_WEAPON){
		num = paramset->AddParam(PARAM_RT_RES, PARAM_MODE_INPUT, WaveSetting::HandleParamInputCtl);
		pWave->NetSizeToString(buff, pWave->m_nRtResource);
		paramset->SetInput(num, PARAMINPUT_RTRES, buff);
	}

	paramset->SetParamStartEnd(0, MAX_PARAM_CNT_ONEPAGE-1);
	return paramset;
}
//����ѡ�����͵Ĳ����ؼ�
int WaveSetting::HandleParamSelectCtl(void * pParam, unsigned int nKey)
{
	int nRst = false;
	ParamSet * paramset = (ParamSet *)pParam;
	Wave * wave = paramset->GetWave();
	PARAM_T * p = (PARAM_T *)paramset->GetCurParam();
	MySelect * sel = (MySelect *)p->control;

	if (nKey == KEY_UP || nKey == KEY_DOWN){
		switch(p->type){
		case PARAM_WORKMODE:
			nRst = sel->SelectItem(nKey - KEY_UP);
			wave->m_nWorkmode = sel->GetValue();
			break;
		case PARAM_TRANSMODE:
			nRst = sel->SelectItem(nKey - KEY_UP);
			wave->m_nTransmode = sel->GetValue();
			break;
		case PARAM_SPEED:
			nRst = sel->SelectItem(nKey - KEY_UP);
			wave->m_nSpeed = sel->GetValue();
			break;
		case PARAM_BANDWIDTH:
			nRst = sel->SelectItem(nKey - KEY_UP);
			wave->m_nBandwidth = sel->GetValue();
			break;
		case PARAM_MODE:
			break;
		default:
			printf("[%s]param type is error<type=%d, key=KEY_UP/KEY_DOWN>", __FUNCTION__, p->type);
			break;
		}
	}
	else if (nKey == KEY_ENTER && paramset->isSelected() == true){
		switch(p->type){
		case PARAM_WORKMODE:
			wave->m_pProtocol->SetWorkMode(wave->m_nWorkmode);
			break;
		case PARAM_TRANSMODE:
			if (wave->m_nTransmode == TRANS_PASSTHROUGH){
				paramset->SetVisible(paramset->GetNum(PARAM_MAC), true);
			}
			else {
				paramset->SetVisible(paramset->GetNum(PARAM_MAC), false);
			}
			wave->m_pProtocol->SetTransMode(wave->m_nTransmode);
			break;
		case PARAM_SPEED:
			wave->m_pProtocol->SetSpeed(wave->m_nSpeed);
			break;
		case PARAM_BANDWIDTH:
			wave->m_pProtocol->SetBandwidth(wave->m_nBandwidth);
			break;
		case PARAM_MODE:
			break;
		default:
			printf("[%s]param type is error<type=%d, key=KEY_ENTER>", __FUNCTION__, p->type);
			break;
		}
	}

	return nRst;
}
//�����������͵Ĳ����ؼ�
int WaveSetting::HandleParamInputCtl(void * pParam, unsigned int nKey)
{
	int nRst = false;
	ParamSet * paramset = (ParamSet *)pParam;
	PARAM_T * p = (PARAM_T *)paramset->GetCurParam();
	ParamInput * input = (ParamInput *)p->control;

	switch(p->type){
	case PARAM_PORT:
		nRst = input->HandleLocalPort(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_REMOTE_PORT:
		nRst = input->HandleRemotePort(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_IP:
		nRst = input->HandleLocalIp(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_REMOTE_IP:
		nRst = input->HandleRemoteIp(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_FREQ:
		nRst = input->HandleFreq(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_MAC:
		nRst = input->HandleMac(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_NET_ID:
		nRst = input->HandleNetId(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	case PARAM_NET_SIZE:
		nRst = input->HandleNetSize(paramset->GetWave(), paramset->isSelected(), nKey);
		break;
	default:
		printf("[%s]type is error<type=%d>", __FUNCTION__, p->type);
		break;
	}

	return nRst;
}

//WaveSetting ���β������ò���=======================================//
//===================================================================//
//��������ĸ��ģ����������ѡ��
int WaveSetting::HandleParamChange(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndSettingParam = station->m_pCurWnd;
	ParamSet * paramset = (ParamSet *)wndSettingParam->GetItemById(ID_WND_PARAMSET|ID_CTL_PARAMSET);

	if (paramset->GetCurParam()->ctl == NULL){
		//����û�п��ƴ�����
		return false;
	}

	if (paramset->GetCurParam()->ctl((void *)paramset, nKey) == true){
		Display::Clear();
		paramset->Draw();
		dlg->Draw();
	}
	return true;
}
//����������˲���
int WaveSetting::ParamBack(void * p, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)p;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndSettingParam = station->m_pCurWnd;
	Wave * wave = station->m_pCurChl->m_pWave;
	ParamSet * paramset = (ParamSet *)wndSettingParam->GetItemById(ID_WND_PARAMSET|ID_CTL_PARAMSET);

	if (paramset->GetCurParam()->ctl == NULL){
		//����û�п��ƴ�����
		return false;
	}

	//����ֵΪFalse����ȡ�����ã�������ǰ�Ĳ���
	if (paramset->GetCurParam()->ctl((void *)paramset, nKey) == false){
		paramset->SetSelected(false);
		wndSettingParam->AddListener(KEY_UP, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_DOWN, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_BACK, RadioStation::Back);
		//�����Ҫ�õ����õ���Ҫȡ��0~9�ļ���
		if (paramset->GetCurParam()->mode == PARAM_MODE_INPUT){
			for (int i=KEY_0; i<=KEY_9; i++){
				wndSettingParam->AddListener(i, NULL);
			}
		}
	}

	Display::Clear();
	paramset->Draw();
	dlg->Draw();
	return true;
}
//��Ӧ�������ý����а�ENTER����ȷ��ѡ��Ĳ���
int WaveSetting::HandleParamEnter(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndSettingParam = station->m_pCurWnd;
	ParamSet * paramset = (ParamSet *)wndSettingParam->GetItemById(ID_WND_PARAMSET|ID_CTL_PARAMSET);

	//��Ҫ������ENTER����Ҫ����һЩ�ı�
	if (paramset->GetCurParam()->ctl != NULL){
		paramset->GetCurParam()->ctl((void *)paramset, nKey);
	}

	if (paramset->isSelected() == true){
		paramset->SetSelected(false);
		wndSettingParam->AddListener(KEY_UP, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_DOWN, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_BACK, RadioStation::Back);
		//�����Ҫ�õ����õ���Ҫȡ��0~9�ļ���
		if (paramset->GetCurParam()->mode == PARAM_MODE_INPUT){
			for (int i=KEY_0; i<=KEY_9; i++){
				wndSettingParam->AddListener(i, NULL);
			}
		}
	}
	else {
		paramset->SetSelected(true);
		wndSettingParam->AddListener(KEY_UP, WaveSetting::HandleParamChange);
		wndSettingParam->AddListener(KEY_DOWN, WaveSetting::HandleParamChange);
		wndSettingParam->AddListener(KEY_BACK, WaveSetting::ParamBack);
		//�����Ҫ�õ����õ���Ҫע��0~9�ļ���
		if (paramset->GetCurParam()->mode == PARAM_MODE_INPUT){
			for (int i=KEY_0; i<=KEY_9; i++){
				wndSettingParam->AddListener(i, WaveSetting::HandleParamChange);
			}
		}
	}

	Display::Clear();
	paramset->Draw();
	dlg->Draw();
	
	if (paramset->isSelected() == false){
		Tooltip msg("����������");
		msg.Show();
		dlg->Draw();
		Sleep(300);
		msg.Resume();
		dlg->Draw();
	}
	return true;
}
//��Ӧ�������ý���������ѡ�����
int WaveSetting::HandleParamSelect(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	Wnd * wndSettingParam = station->m_pCurWnd;
	ParamSet * paramset = (ParamSet *)wndSettingParam->GetItemById(ID_WND_PARAMSET|ID_CTL_PARAMSET);

	if (paramset->Switch(nKey) == true){
		Display::Clear();
		paramset->Draw();
		dlg->Draw();
	}
	return 0;
}
//��ʼ���������ý���
int WaveSetting::Init(void * pStation, unsigned int nKey)
{
	RadioStation * station = (RadioStation *)pStation;
	CSimulatorDlg *dlg = (CSimulatorDlg *)station->m_pDlg;
	ParamSet * paramset = NULL;
	//������������ڵĻ��������в�������
	if (station->m_pCurChl->m_pWave == NULL){
		return false;
	}

	Wnd * wndSettingParam = new Wnd(WND_WAVESET);
	wndSettingParam->SetFather(station->m_pCurWnd);
	station->m_pCurWnd = wndSettingParam;

	Wave * pWave = station->m_pCurChl->m_pWave;
	if (pWave == NULL){
		printf("[%s]wave is not existed\n", __FUNCTION__);
		return false;
	}
	else if (pWave->m_nType >= WAVE_UNLOAD){
		printf("[%s]wave type error<m_nType=%d>\n", __FUNCTION__, pWave->m_nType);
		return false;
	}

	paramset = WaveSetting::SetWave(pWave);
	if (paramset != NULL){
		wndSettingParam->AddControl(CTL_WAVESET, ID_WND_PARAMSET|ID_CTL_PARAMSET, (void *)paramset);
		wndSettingParam->AddListener(KEY_UP, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_DOWN, WaveSetting::HandleParamSelect);
		wndSettingParam->AddListener(KEY_ENTER, WaveSetting::HandleParamEnter);
		wndSettingParam->AddListener(KEY_BACK, RadioStation::Back);
	}
	else {
		printf("[%s]wave setting init error\n", __FUNCTION__);
		return false;
	}
	
	Display::Clear();
	wndSettingParam->Layout();
	dlg->Draw();
	return true;
}
//===================================================================//