//#ifndef _CALL_H_
//#define _CALL_H_
#pragma once

class Call
{
public:
	//��ʼ�����Ž���
	static int Init(void * pStation, unsigned int nKey);
	//��������绰����
	static int HandleInputCallNumber(void * pStation, unsigned int nKey);
	//����ѡ��ͨ����ͨ��
	static int HandleSelectCallChl(void * pStation, unsigned int nKey);
	//����ͨ��
	static int HandleCalling(void * pStation, unsigned int nKey);
	//�������
	static int HandleBackspace(void * pStation, unsigned int nKey);
};

//#endif 