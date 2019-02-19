#include "stdafx.h"
#include "TestThreadPool.h"


CTestThreadPool::CTestThreadPool(void)
{
	smp=NULL;
	isExitThread=true;
	CreateThreadNum=0;
	RunThreadNum=0;
	MaxThreadNum=0;
}


CTestThreadPool::~CTestThreadPool(void)
{

}

bool CTestThreadPool::CreateTestThread(int minCount,int maxCount)
{
	if(minCount<1||minCount>maxCount)
		return false;
	//创建信号量
	smp=CreateSemaphore(NULL,0,maxCount,NULL);
	//创建最小数量的线程
	for(int i=0;i<minCount;i++)
	{
		HANDLE pe=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,NULL);
		if(pe)
		{
			pes.push_back(pe);
		}
	}
	CreateThreadNum=minCount;
	MaxThreadNum=maxCount;
	return true;
}
unsigned __stdcall CTestThreadPool::ThreadPro(void*lpvoid)
{
	CTestThreadPool*thiz=(CTestThreadPool*)lpvoid;
	CTestTask* task=NULL;
	while(thiz->isExitThread)
	{
		if(WaitForSingleObject(thiz->smp,100)==WAIT_TIMEOUT)
		{
			continue;
		}
		thiz->mylock.TestLock();
		thiz->RunThreadNum++;
		thiz->mylock.TestUnlock();
		while(!thiz->tasks.empty())
		{
			thiz->mylock.TestLock();
			task=thiz->tasks.front();
			thiz->tasks.pop();
			thiz->mylock.TestUnlock();
			task->MakeTask();
			delete task;
			task=NULL;
		}
		thiz->mylock.TestLock();
		thiz->RunThreadNum--;
		thiz->mylock.TestUnlock();
	}
	return 0;
}
void CTestThreadPool::DestoryTestThread()
{
	isExitThread=false;
	auto ite=pes.begin();
	while(ite!=pes.end())
	{
		if(WaitForSingleObject(*ite,100)==WAIT_TIMEOUT)
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite=NULL;
		++ite;
	}
	CTestTask*del=NULL;
	while(!this->tasks.empty())
	{
		del=tasks.front();
		tasks.pop();
		delete del;
		del=NULL;
	}
	CloseHandle(smp);
	smp=NULL;
}
bool CTestThreadPool::AddTask(CTestTask* task)
{
	if(task==NULL)
		return false;
	mylock.TestLock();
	tasks.push(task);
	mylock.TestUnlock();
	if(RunThreadNum<CreateThreadNum)
	{
		ReleaseSemaphore(smp,1,NULL);
	}else if(CreateThreadNum<MaxThreadNum)
	{
		//创建线程
		HANDLE pe=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,NULL);
		pes.push_back(pe);
		CreateThreadNum++;
		ReleaseSemaphore(smp,1,NULL);
	}
	return true;
}