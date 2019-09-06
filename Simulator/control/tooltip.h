//#ifndef _TOOLTIP_H_
//#define _TOOLTIP_H_
#pragma once
#include "../mmi/display.h"
#include "../option.h"

#define MAX_MSG_SIZE	16

class Tooltip
{
public:
	Tooltip(char * pszMsg);
	~Tooltip();

public:
	void Show();
	void Resume();
	RECT_T * GetRect(){
		return &m_tRect;
	};

private:
	RECT_T m_tRect;
	char m_szMessage[MAX_MSG_SIZE+1];
	char * m_pszBackup;
};

//#endif