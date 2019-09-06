//#ifndef _CALL_H_
//#define _CALL_H_
#pragma once

class Call
{
public:
	//初始化拨号界面
	static int Init(void * pStation, unsigned int nKey);
	//处理输入电话号码
	static int HandleInputCallNumber(void * pStation, unsigned int nKey);
	//处理选择通话的通道
	static int HandleSelectCallChl(void * pStation, unsigned int nKey);
	//处理通话
	static int HandleCalling(void * pStation, unsigned int nKey);
	//处理回退
	static int HandleBackspace(void * pStation, unsigned int nKey);
};

//#endif 