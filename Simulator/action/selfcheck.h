//#ifndef _SELFCHECH_H_
//#define _SELFCHECH_H_
#pragma once

class SelfCheck
{
public:
	static int PanelTest();
	static int ServiceTest();
	static int MFSTest();
	static int RFTest();
	static int PowerTest();
	static int TDTest();
	static void Init(void * pStation);
};

//#endif