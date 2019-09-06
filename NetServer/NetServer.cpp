// NetServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WINSOCK2.H>  
#include <Windows.h>
  
#pragma comment(lib,"WS2_32.lib")  

#define LOCAL_IP		"192.168.1.11"
#define LOCAL_PORT		8600
#define BUF_SIZE		256 

#define RST_OK			(0)
#define RST_PARAM_ERROR	(-1)
#define RST_CMD_INVALID	(-2)
#define RST_EXIT		(1)
#define RST_HELP		(2)

enum
{
	TYPE_INT = 0,
	TYPE_HEX,
	TYPE_STRING,
	TYPE_MAX
};

struct param_t
{
	unsigned int type;
	unsigned short param[8];
};

typedef enum
{
//user
	PARAM_WORKMODE = 0, //工作模式，战斗，低截获
	PARAM_TRANSMODE, //转发模式，透传，代理
	PARAM_MODE, //跳频，定频
	PARAM_FREQ, //频率
	PARAM_SPEED, //速率
	PARAM_BANDWIDTH, //带宽
	PARAM_IP, //本地IP
	PARAM_PORT, //本地端口
	PARAM_MAC, //上位机MAC
	PARAM_REMOTE_IP, //上位机IP
	PARAM_REMOTE_PORT, //上位机端口
	PARAM_NET_ID, //波形网络ID
	PARAM_NET_SIZE, //网络规模
//debug
	//PARAM_FREE, //网络规模
	PARAM_MAX
}PARAM_TYPE;

typedef struct cmd_t
{
	PARAM_TYPE type;
	char cmdname[32];
	int (* callcack)(int, void *);
}CMD_T;

static int hanldeWorkMode(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeWorkMode]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	//do....

	printf("[hanldeWorkMode]:workmode = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int hanldeTransMode(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeTransMode]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeTransMode]:transmode = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int handleMode(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	//if (paramCnt != 1){
	printf("ERROR[handleMode]:paramCnt = %d\n", paramCnt);
	//	return RST_PARAM_ERROR;
	//}

	printf("[handleMode]:mode = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int handleFreq(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[handleFreq]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[handleFreq]:freq = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int handleSpeed(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[handleSpeed]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[handleSpeed]:speed = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int handleBandwidth(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[handleBandwidth]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[handleBandwidth]:bandwidth = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int hanldeLocalIP(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 4){
		printf("ERROR[hanldeLocalIP]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeLocalIP]:ip = %d.%d.%d.%d\n", (int)paramValue[0],
		(int)paramValue[1],(int)paramValue[2],(int)paramValue[3]);
	return RST_OK;
}

static int hanldeLocalPort(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeLocalPort]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeLocalPort]:port = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int hanldeMAC(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 6){
		printf("ERROR[hanldeMAC]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeMAC]:MAC = %x:%x:%x:%x:%x:%x\n", (int)paramValue[0],
		(int)paramValue[1],(int)paramValue[2],(int)paramValue[3],(int)paramValue[4],(int)paramValue[5]);
	return RST_OK;
}

static int hanldeRemoteIP(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 4){
		printf("ERROR[hanldeRemoteIP]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeRemoteIP]:remote ip = %d.%d.%d.%d\n", (int)paramValue[0],
		(int)paramValue[1],(int)paramValue[2],(int)paramValue[3]);

	return RST_OK;
}

static int hanldeRemotePort(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeRemotePort]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeRemotePort]:remote port = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int hanldeNetId(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeNetId]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeNetId]:net id = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static int hanldeNetSize(int wParam, void * lParam)
{
	int paramCnt = wParam;
	long * paramValue = (long *)lParam;

	if (paramCnt != 1){
		printf("ERROR[hanldeNetSize]:paramCnt = %d\n", paramCnt);
		return RST_PARAM_ERROR;
	}

	printf("[hanldeNetSize]:net size = %d\n", (int)paramValue[0]);
	return RST_OK;
}

static CMD_T cmd_tbl[] = {
	{PARAM_WORKMODE, "workmode", hanldeWorkMode},
	{PARAM_TRANSMODE, "transmode", hanldeTransMode},
	{PARAM_MODE, "mode", handleMode},
	{PARAM_FREQ, "freq", handleFreq},
	{PARAM_SPEED, "speed", handleSpeed},
	{PARAM_BANDWIDTH, "bw", handleBandwidth},
	{PARAM_IP, "localip", hanldeLocalIP},
	{PARAM_PORT, "localport", hanldeLocalPort},
	{PARAM_MAC, "mac", hanldeMAC},
	{PARAM_REMOTE_IP, "remoteip", hanldeRemoteIP},
	{PARAM_REMOTE_PORT, "remoteport", hanldeRemotePort},
	{PARAM_NET_ID, "netid", hanldeNetId},
	{PARAM_NET_SIZE, "netsize", hanldeNetSize},
};

static int ParseParam(char * param)
{
	unsigned int len = strlen(param), i=0;
	long value = 0;
	int bHex = false;

	//判断是否是十六进制的
	for (i=0; i<len; i++){
		if (param[i]>='a' && param[i]<='f' || param[i]>='A' && param[i]<='F'){
			bHex = true;
			break;
		}
	}

	if (bHex == true){
		char * szHex = param;
		int m=0, n=0, length=strlen(szHex);
		for (m=0; m<length; m++){
			char c = szHex[m];
			int multi = 1;
			if (c >= '0' && c <= '9'){
				c -= 0x30;
			}
			else if (c >= 'a' && c <= 'f'){
				c = c - 'a' + 10;
			}
			else if (c >= 'A' && c <= 'F'){
				c = c - 'A' + 10;
			}
			for (n=0; n<length-m-1; n++){
				multi *= 16;
			}
			value += (c*multi);
		}
	}
	else{
		value = atol(param);
	}

	return value;
}

static int CmdHandle(char * cmd, char * param)
{
	int i = 0, paramCnt=0, num=0;
	long paramValue[8];
	char temp[32];

	//确定参数个数
	if (param != NULL){
		for (i=0; i<strlen(param); i++){
			//解析参数
			if (param[i] == ' '){
				paramValue[paramCnt] = ParseParam(temp);
				memset(temp, 0, sizeof(char)*32);
				num = 0;
				paramCnt ++;
			}
			else {
				temp[num++] = param[i];
			}
		}
	}
	int size = sizeof(cmd_tbl)/sizeof(CMD_T);
	for (i=0; i<sizeof(cmd_tbl)/sizeof(CMD_T); i++){
		//if (type == cmd_tbl[i].type){
		if (strcmp(cmd, cmd_tbl[i].cmdname) == 0){
			return cmd_tbl[i].callcack(paramCnt, (void *)&paramValue);
		}
	}
	return RST_CMD_INVALID;
}

static int ParseCmd(char * cmdline)
{
	unsigned short paramCnt=0,i=0,j=0;
	unsigned int cmdLength = strlen(cmdline);
	char cmd[32];
	int rst = 0;

	//解析指令类型
	memset(cmd, 0, sizeof(char)*32);
	for (i=0; i<cmdLength; i++){
		char c = cmdline[i];
		if (c != ' '){
			cmd[i] = c;
		}
		else {
			break;
		}
	}

	//如果命令是"exit"，或者是"help"不用解析参数
	if (strcmp(cmd, "help") == 0){
		return RST_HELP;
	}
	else if (strcmp(cmd, "exit") == 0){
		return RST_EXIT;
	}

	if (i == cmdLength-1){
		//没有参数
		rst = CmdHandle(cmd, NULL);
	}
	else {
		//解析参数
		//确定参数个数
		char * param = &cmdline[i+1];
		rst = CmdHandle(cmd, param);
	}

	return rst;
}

#define KHZ		(1000)
#define MHZ		(1000*1000)
#define GHZ		(1000*1000*1000)

void FreqToInt(char * buff)
{
	int i=0, j=0, m=0, n=0;
	char freq[4] = {0};
	long m_nFreq;

	memset(freq, 0, sizeof(char)*4);
	for (i=0; i<strlen(buff); i++){
		char c = buff[i];
		//如果没有'.'而直接发现非0~9的字符，则说明"30MHz"这种情况的输入
		if (c == '.' || c < '0' || c > '9'){
			m = atoi(freq);
			j = 0;
			break;
		}
		else {
			freq[j++] = c;
		}
	}

	//之后在找到'.'的时候，才需要解析小数点后面
	if (buff[i] == '.'){
		for (i=i+1; i<strlen(buff); i++){
			char c = buff[i];
			if (c >= '0' && c<= '9'){
				freq[j++] = c;
			}
			else {
				n = atoi(freq);
				j = 0;
				break;
			}
		}
	}

	if (buff[i] == 'K'){
		m_nFreq = m*KHZ + n;
	}
	else if (buff[i] == 'M'){
		m_nFreq = m*MHZ + n*KHZ;
	}
	else if (buff[i] == 'G'){
		m_nFreq = m*GHZ + n*MHZ;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	SOCKADDR_IN addrSrv; 
	SOCKADDR_IN addrClient; 
	SOCKET s;
	char szCmdLine[BUF_SIZE];
	int nRst,len = sizeof(SOCKADDR); 
	WSADATA wsd;

	// 初始化套接字动态库  
	if(WSAStartup(MAKEWORD(2,2),&wsd) != 0){  
		printf("WSAStartup failed !/n");  
		return 1;  
	} 
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s == INVALID_SOCKET){  
		printf("socket() failed ,Error Code:%d\n",WSAGetLastError());  
		WSACleanup();  
		return 1;  
	}  

	// 设置服务器地址  
	ZeroMemory(szCmdLine,BUF_SIZE);  
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);  
	addrSrv.sin_family = AF_INET;  
	addrSrv.sin_port = htons(8808);

	printf("create socket ok!\n");
	// 绑定套接字  
	nRst = bind(s, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));  
	if(SOCKET_ERROR == nRst){     
		printf("bind failed !\n");     
		closesocket(s);     
		WSACleanup();     
		return -1;     
	}  
	printf("bind ok!\n");
	while (1){
		char szRst[32];
		memset(szCmdLine, 0, sizeof(char)*BUF_SIZE);
		nRst = recvfrom(s,szCmdLine, BUF_SIZE, 0, (SOCKADDR*)&addrClient, &len);  	
		//printf("%x",s);
		if(SOCKET_ERROR == nRst)     
		{     
			printf("recvfrom failed !/n");     
			closesocket(s);     
			WSACleanup();     
			return -1;     
		}  
		printf("Recv From Client:%s\n",szCmdLine);
		nRst = ParseCmd(szCmdLine);

		memset(szRst, 0, sizeof(char)*32);
		switch (nRst){
		case RST_OK:
			sprintf_s(szRst, "OK"); 
			break;
		case RST_CMD_INVALID:
			sprintf_s(szRst, "Cmd Invalid");  
			break;
		case RST_PARAM_ERROR:
			sprintf_s(szRst, "Param Error");
			break;
		case RST_HELP:
			sprintf_s(szRst, "Help");
			break;
		case RST_EXIT:
			sprintf_s(szRst, "Exit");
			break;
		}
		sendto(s, szRst, sizeof(szRst), 0,(SOCKADDR*)&addrClient,len);  

		if (nRst == RST_EXIT){
			break;
		}
	}
	closesocket(s);
	WSACleanup();
	return 0;
}

