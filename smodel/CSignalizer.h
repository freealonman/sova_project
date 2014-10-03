#ifndef _CSIGNALIZER_H_
#define _CSIGNALIZER_H_

#include "main.h"

class CSignalizer
{
private:
	Socket		     tcpSocket;
	string		     ipAdress;	  
	unsigned long tcpPort;
	void SendDataToVss();
	static DWORD WINAPI SovaDataServer(PVOID pParam);
public:
	CSignalizer(const string& IP, const string& PORT);
	void Start(SVSSData* DATA);
	void Stop();
};