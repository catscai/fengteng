#pragma once
#include<Windows.h>
#include<process.h>
#include<queue>
#include<list>
#include<vector>
using namespace std;
class CTestLock
{
private:
	CRITICAL_SECTION lock;
public:
	CTestLock(){
		InitializeCriticalSection(&lock);
	}
	~CTestLock(){
		DeleteCriticalSection(&lock);
	}
public:
	void TestLock()
	{
		EnterCriticalSection(&lock);
	}
	void TestUnlock()
	{
		LeaveCriticalSection(&lock);
	}
};
class CTestTask
{
public:
	CTestTask(){}
	~CTestTask(){}
public:
	virtual void MakeTask()=0;
};
class CTestThreadPool
{
public:
	queue<CTestTask*> tasks;	//�������
	HANDLE smp;					//�ź���
	vector<HANDLE> pes;			//�߳�����
	bool isExitThread;			//�˳���־
	int CreateThreadNum;
	int RunThreadNum;
	int MaxThreadNum;
	CTestLock mylock;
public:
	CTestThreadPool(void);
	~CTestThreadPool(void);
public:
	bool CreateTestThread(int minCount,int maxCount);
	void DestoryTestThread();
	bool AddTask(CTestTask* task);
	static unsigned __stdcall ThreadPro(void*lpvoid);
};

