#pragma once
#include <Windows.h>
#define MYQUEUE_INIT_SIZE 50
template<class T>
class CMyQueue
{
private:
	struct Queue{
		int front;
		int rear;
		int length;
		T data[MYQUEUE_INIT_SIZE];
	};
private:
	Queue Q;
	CRITICAL_SECTION lock1,lock2,lock3;
	int size;
	T t;
private:
	bool AddNode(T data)
	{
		if(Q.front==(Q.rear+1)%Q.length)	//已经满了
			return false;
		EnterCriticalSection(&lock1);
		if(Q.front==(Q.rear+1)%Q.length){	//已经满了
			LeaveCriticalSection(&lock1);
			return false;
		}
		Q.data[Q.rear]=data;
		Q.rear=(Q.rear+1)%Q.length;
		LeaveCriticalSection(&lock1);
		size++;
		return true;
	}
	bool IsEmpty()
	{
		if(Q.front==Q.rear)
			return true;
		return false;
	}
	bool IsFull()
	{
		if(Q.front==(Q.rear+1)%Q.length)
			return true;
		return false;
	}
	bool DeleteNode()
	{
		if(Q.front==Q.rear)		//队列为空
			return false;
		EnterCriticalSection(&lock2);
		if(Q.front==Q.rear)		//队列为空
		{
			LeaveCriticalSection(&lock2);
			return false;
		}

		Q.front=(Q.front+1)%Q.length;
		LeaveCriticalSection(&lock2);
		size--;
		return true;
	}
	void ClearQueue()
	{
		Q.front=Q.rear=0;
		size=0;
	}
	T FrontNode()
	{
		EnterCriticalSection(&lock3);
		t=Q.data[Q.front];
		LeaveCriticalSection(&lock3);
		return t;
	}
public:
	CMyQueue(void)
	{
		Q.front=0;
		Q.rear=0;
		Q.length=MYQUEUE_INIT_SIZE;
		size=0;
		InitializeCriticalSection(&lock1);
		InitializeCriticalSection(&lock2);
		InitializeCriticalSection(&lock3);
	}
	~CMyQueue(void)
	{
		DeleteCriticalSection(&lock1);
		DeleteCriticalSection(&lock2);
		DeleteCriticalSection(&lock3);
	}
public:
	bool push(T data)
	{
		return this->AddNode(data);
	}
	bool pop()
	{
		return this->DeleteNode();
	}
	void clear()
	{
		this->ClearQueue();
	}
	T front()
	{
		return this->FrontNode();
	}
	bool empty()
	{
		return this->IsEmpty();
	}
	bool full()
	{
		return this->IsFull();
	}
};

