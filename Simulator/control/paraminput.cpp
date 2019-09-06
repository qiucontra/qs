#include "stdafx.h"
#include "paraminput.h"

ParamInput::ParamInput(unsigned int nX, unsigned int nY, unsigned int nWidth, unsigned int nHeight, FONT_SIZE eFont)
{
	m_tRect.x = nX;
	m_tRect.y = nY;
	m_tRect.width = nWidth;
	m_tRect.height = nHeight;
	m_eFont = eFont;
	m_nInputNum = 0;
	m_nValue = 0;
	m_bShift = false;
}

ParamInput::ParamInput(RECT_T tRect, FONT_SIZE eFont)
{
	ParamInput(tRect.x, tRect.y, tRect.width, tRect.height, eFont);
}

ParamInput::~ParamInput()
{

}

int ParamInput::HandleFreq(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "---.---MHz");
			m_nOrder = FREQ_UNIT_MHZ;
			m_nInputNum = 0;
		}
		else {
			pWave->FreqToInt(m_szValue, &pWave->m_nFreq);
			pWave->FreqToString(m_szValue, pWave->m_nFreq);
			return true;
		}
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 7){
			int number = nKey;
			m_szValue[m_nInputNum] = number+0x30;
			if ((m_nInputNum+2) % 4 == 0){
				m_nInputNum += 2;
			}
			else {
				m_nInputNum ++;
			}
			return true;
		}
	}
	else if (nKey == KEY_UP){
		if (m_nOrder > FREQ_UNIT_GHZ){
			m_nOrder --;
			char * unit = Wave::GetFreqUnitName(m_nOrder);
			for (int i=0; i<3; i++){
				m_szValue[7+i] = unit[i];
			}
			return true;
		}
	}
	else if (nKey == KEY_DOWN){
		if (m_nOrder < FREQ_UNIT_MAX-1){
			m_nOrder ++;
			char * unit = Wave::GetFreqUnitName(m_nOrder);
			for (int i=0; i<3; i++){
				m_szValue[7+i] = unit[i];
			}
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			if (m_nInputNum % 4 == 0){
				m_nInputNum -= 2;
			}
			else {
				m_nInputNum --;
			}
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			pWave->FreqToString(m_szValue, pWave->m_nFreq);
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleLocalPort(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "----");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->PortToInt(m_szValue, &pWave->m_nLocalPort);
			pWave->m_pProtocol->SetLocalPort(pWave->m_nLocalPort);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 4){
			m_szValue[m_nInputNum++] = (nKey-KEY_0)+0x30;
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			m_nInputNum --;
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			int res = pWave->m_nLocalPort;
			for (int i=3; i>=0; i--){
				int num = (res % 10);
				res = (res / 10);
				m_szValue[i] = num + 0x30;
			}
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleRemotePort(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "----");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->PortToInt(m_szValue, &pWave->m_nRemotePort);
			pWave->m_pProtocol->SetLocalPort(pWave->m_nRemotePort);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 4){
			m_szValue[m_nInputNum++] = (nKey-KEY_0)+0x30;
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			m_nInputNum --;
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			int res = pWave->m_nRemotePort;
			for (int i=3; i>=0; i--){
				int num = (res % 10);
				res = (res / 10);
				m_szValue[i] = num + 0x30;
			}
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleLocalIp(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			//开始进行IP设置
			STRCPY(m_szValue, "---.---.---.---");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->IpToInt(m_szValue, pWave->m_nLocalIp);
			pWave->IpToString(m_szValue, pWave->m_nLocalIp);
			pWave->m_pProtocol->SetLocalIp(pWave->m_nLocalIp);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 15){
			m_szValue[m_nInputNum] = (nKey-KEY_0)+0x30;
			if ((m_nInputNum+2) % 4 == 0){
				m_nInputNum += 2;
			}
			else {
				m_nInputNum ++;
			}
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			if (m_nInputNum % 4 == 0 && m_nInputNum != 0){
				m_nInputNum -= 2;
			}
			else {
				m_nInputNum --;
			}
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			pWave->IpToString(m_szValue, pWave->m_nLocalIp);
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleRemoteIp(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			//开始进行IP设置
			STRCPY(m_szValue, "---.---.---.---");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->IpToInt(m_szValue, pWave->m_nRemoteIp);
			pWave->IpToString(m_szValue, pWave->m_nRemoteIp);
			pWave->m_pProtocol->SetRemoteIp(pWave->m_nRemoteIp);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 15){
			m_szValue[m_nInputNum] = (nKey-KEY_0)+0x30;
			if ((m_nInputNum+2) % 4 == 0){
				m_nInputNum += 2;
			}
			else {
				m_nInputNum ++;
			}
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			if (m_nInputNum % 4 == 0 && m_nInputNum != 0){
				m_nInputNum -= 2;
			}
			else {
				m_nInputNum --;
			}
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			pWave->IpToString(m_szValue, pWave->m_nRemoteIp);
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleMac(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			//开始进行IP设置
			STRCPY(m_szValue, "--:--:--:--:--:--");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->MacToInt(m_szValue, pWave->m_nMac);
			pWave->m_pProtocol->SetMac(pWave->m_nMac);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 17){
			if (m_bShift == true){
				if (nKey >= KEY_1 && nKey <= KEY_6){
					m_szValue[m_nInputNum] = (nKey-KEY_1)+'A';
				}
				else {
					return false;
				}
			}
			else {
				m_szValue[m_nInputNum] = (nKey-KEY_0)+0x30;
			}	

			if ((m_nInputNum+2) % 3 == 0){
				m_nInputNum += 2;
			}
			else {
				m_nInputNum ++;
			}
			return true;
		}
	}
	else if (nKey == KEY_UP){
		if (m_bShift == true){
			m_bShift = false;
		}
		else {
			m_bShift = true;
		}
		return true;
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			if (m_nInputNum % 3 == 0 && m_nInputNum != 0){
				m_nInputNum -= 2;
			}
			else {
				m_nInputNum --;
			}
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			pWave->MacToString(m_szValue, pWave->m_nMac);
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleNetId(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "--");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->NetIdToInt(m_szValue, &pWave->m_nNetId);
			pWave->m_pProtocol->SetNetId(pWave->m_nNetId);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 2){
			m_szValue[m_nInputNum++] = (nKey-KEY_0)+0x30;
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			m_nInputNum --;
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			int res = pWave->m_nNetId;
			for (int i=1; i>=0; i--){
				int num = (res % 10);
				res = (res / 10);
				m_szValue[i] = num + 0x30;
			}
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleNetSize(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "--");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->NetIdToInt(m_szValue, &pWave->m_nNetSize);
			pWave->m_pProtocol->SetNetId(pWave->m_nNetSize);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 2){
			m_szValue[m_nInputNum++] = (nKey-KEY_0)+0x30;
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			m_nInputNum --;
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			int res = pWave->m_nNetSize;
			for (int i=1; i>=0; i--){
				int num = (res % 10);
				res = (res / 10);
				m_szValue[i] = num + 0x30;
			}
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

int ParamInput::HandleRtResource(Wave * pWave, unsigned int bSelected, unsigned int nKey)
{
	if (nKey == KEY_ENTER){
		if (bSelected == false){
			STRCPY(m_szValue, "--");
			m_nInputNum = 0;
		}
		else {
			//如果再次点击ENTER后，确定输入的值
			pWave->NetIdToInt(m_szValue, &pWave->m_nRtResource);
			pWave->m_pProtocol->SetNetId(pWave->m_nRtResource);
		}
		return true;
	}
	else if (nKey >= KEY_0 && nKey <= KEY_9){
		if (m_nInputNum < 2){
			m_szValue[m_nInputNum++] = (nKey-KEY_0)+0x30;
			return true;
		}
	}
	else if (nKey == KEY_BACK){
		if (m_nInputNum != 0){
			m_nInputNum --;
			m_szValue[m_nInputNum] = '-';
			return true;
		}
		else {
			//直接退出，执行KEY_ENTER
			int res = pWave->m_nRtResource;
			for (int i=1; i>=0; i--){
				int num = (res % 10);
				res = (res / 10);
				m_szValue[i] = num + 0x30;
			}
			return false;
		}
	}
	else {
		printf("[%s]nKey value error<nKey=%d>\n", __FUNCTION__, nKey);
	}
	return false;
}

void ParamInput::Draw()
{
	Display::Clear(m_tRect.x, m_tRect.y, m_tRect.width, m_tRect.height);
	Display::PrintString(m_szValue, m_tRect.x, m_tRect.y, m_eFont);
}
