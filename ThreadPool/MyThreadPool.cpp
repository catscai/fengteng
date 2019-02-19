#include "stdafx.h"
#include "MyThreadPool.h"

//bool CPublicThreadPool::ThreadPoolflag=true;
//shared_ptr<CMyThreadPool*> CPublicThreadPool::pool=NULL;
//shared_ptr<CMyThreadPool*> CPublicThreadPool::getThreadPool(int minCount,int maxCount)
//{
//	if(ThreadPoolflag)
//	{
//		CMyThreadPool *temp=new CMyThreadPool;
//		pool=(shared_ptr<CMyThreadPool*>)temp;
//		temp->CreateMyThreadPool(minCount,maxCount);
//		return pool;
//	}
//	return NULL;
//}
//void CPublicThreadPool::AddTask()
//{
//	
//}

CMyThreadPool::CMyThreadPool(void)
{
	flagQuit=true;
	createThreadNum=0;
	runThreadNum=0;
	maxThreadNum=0;
	this->sepm=NULL;
}
CMyThreadPool::~CMyThreadPool(void)
{
	cout<<"~CMyThreadPool()"<<endl;
}
bool CMyThreadPool::CreateMyThreadPool(int minCount,int maxCount)
{
	if(minCount<=0||minCount>maxCount)
		return false;
	//创建信号量
	sepm=CreateSemaphore(NULL,0,maxCount,NULL);
	for(int i=0;i<minCount;i++)
	{
		HANDLE hand=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,0);
		if(hand)
		{
			pes.push_back(hand);
		}
	}
	this->maxThreadNum=maxCount;
	this->createThreadNum=minCount;

	return true;
}
void CMyThreadPool::DestoryThreadPool()
{
	this->flagQuit=false;
	auto ite=pes.begin();
	while(ite!=pes.end())
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite=NULL;
		++ite;
	}
	if(sepm)
		CloseHandle(sepm);
	sepm=NULL;
	CMyTask*temp;
	while(!mytasks.empty())
	{
		temp=mytasks.front();
		mytasks.pop();
		delete temp;
		temp=NULL;
	}
}
bool CMyThreadPool::AddTask(CMyTask* mytask)
{
	if(mytask==NULL)
		return false;
	//加入任务队列
	while(true)
	{
		if(!mytasks.full())
		{
			mytasks.push(mytask);
			break;
		}
	}
	if(runThreadNum<createThreadNum)
	{
		ReleaseSemaphore(this->sepm,1,NULL);
	}else if(createThreadNum<maxThreadNum)
	{
		HANDLE hand=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,0);
		if(hand){
			//加入句柄链表
			pes.push_back(hand);
		}
		createThreadNum++;
		ReleaseSemaphore(this->sepm,1,NULL);
	}
	return true;
}
unsigned __stdcall CMyThreadPool::ThreadPro( void * lpvoid )
{
	CMyThreadPool*thiz=(CMyThreadPool*)lpvoid;
	CMyTask* temp=NULL;
	while(thiz->flagQuit)
	{
		if(WaitForSingleObject(thiz->sepm,100)==WAIT_TIMEOUT)
			continue;
		//运行线程数量++
		thiz->mylock.Lock();
		thiz->runThreadNum++;
		thiz->mylock.UnLock();
		while(!thiz->mytasks.empty())
		{
			temp=thiz->mytasks.front();
			thiz->mytasks.pop();
			temp->RunTask();
			//执行后删除任务
			delete temp;
			temp=NULL;
		}
		thiz->runThreadNum--;
	}
	return 0;
}