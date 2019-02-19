
#pragma once
#ifndef UDPMEDIATOR_H
#define UDPMEDIATOR_H
#include "UDPNet.h"
#include "Packdef.h"
#include <map>
#include <vector>
using namespace std;
//����Э��ӳ���
class UDPMediator;//ǰ������
typedef bool (UDPMediator::*PDEAL)(char*);
typedef struct ProtectMegMap
{
	PackType ptype;
	PDEAL pfMeg;
}ProtectMegMap;
class UDPMediator:public IMediator
{
public:
	UDPNet* m_udpNet;
	long m_userid;			//��¼�ɹ����˺�
	bool m_isLoginFlag;		//��������Ƿ��Ѿ���¼�ɹ�

public:
	UDPMediator();
	~UDPMediator();
public:
	virtual bool OpenServer();
	virtual void CloseServer();
	virtual void DealData(char*szbuf);
	virtual bool SendData(char*szbuf,int len);
public:
	bool OnCloseClient(char*szbuf);		//�յ���Ϣ���رտͻ���
	bool OnRegisterRqId(char*szbuf);	//�յ���Ϣ������userid
	bool OnPublicWord(char*szbuf);		//�յ���Ϣ�����ع���
	bool OnLoginSuccess(char*szbuf);	//��¼�ɹ���Ϣ
	bool OnLoginFailture(char*szbuf);	//��¼ʧ����Ϣ
	bool OnRegisterSuccess(char*szbuf);	//ע��ɹ���Ϣ
	bool OnRecvMovieLink(char*szbuf);	//���ߺ��յ������������ĵ�Ӱ����
	bool OnSerachMovieRs(char*szbuf);	//��ѯ��Ƶ �ظ�
	bool OnSerachMovieInfoRs(char*szbuf);//��ѯ��Ƶ ��Ƶ��Ϣ�ظ�
	bool OnCollectRs(char*szbuf);		//�ղ���Ƶ�ظ�
	bool OnDeleteCollectionRs(char*szbuf);	//ɾ���ղ��� �ظ�
};

#endif