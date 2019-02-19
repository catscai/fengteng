#pragma once
#include<Windows.h>
#include<process.h>
#include "MyQueue.h"
#include<queue>
#include<list>
#include<iostream>
//#include<memory>
using namespace std;

class CMyLock
{
private:
	CRITICAL_SECTION lock;
public:
	CMyLock(){
		InitializeCriticalSection(&lock);
	}
	~CMyLock(){
		DeleteCriticalSection(&lock);
	};
public:
	void Lock()
	{
		EnterCriticalSection(&lock);
	}
	void UnLock()
	{
		LeaveCriticalSection(&lock);
	}
};
class CMyTask
{
public:
	CMyTask(){}
	virtual ~CMyTask(){}
public:
	virtual void RunTask()=0;
};
class CMyThreadPool
{
private:
	CMyQueue<CMyTask*> mytasks;	//任务队列
	list<HANDLE> pes;			//线程链表
	int createThreadNum;		//当前线程数量
	volatile int runThreadNum;			//正在使用的线程数量
	int maxThreadNum;			//最大限制线程数量
	bool flagQuit;				//线程退出开关
	HANDLE sepm;				//信号量
	CMyLock mylock;				//线程锁 实现线程同步
public:
	CMyThreadPool(void);
	~CMyThreadPool(void);
public:
	bool CreateMyThreadPool(int minCount,int maxCount);
	void DestoryThreadPool();
	bool AddTask(CMyTask* mytask);
	static unsigned __stdcall ThreadPro( void * lpvoid);
};
//class CPublicThreadPool
//{
//public:
//	CMyThreadPool*pool;
//public:
//	CPublicThreadPool(){
//		pool=new CMyThreadPool;
//	};
//	~CPublicThreadPool(){
//		if(pool){
//			pool->DestoryThreadPool();
//			delete pool;
//		}
//	};
//};
//class CPublicThreadPool
//{
//private:
//	static shared_ptr<CMyThreadPool*> pool;
//	static bool ThreadPoolflag;
//private:
//	CPublicThreadPool(){}
//	~CPublicThreadPool(){}
//public:
//	static shared_ptr<CMyThreadPool*> getThreadPool(int minCount,int maxCount);
//	void AddTask();
//};

