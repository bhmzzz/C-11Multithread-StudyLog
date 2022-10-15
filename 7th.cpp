#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>
#include <windows.h>
using namespace std;

#define _WINDOWSJQ_ 1

class CWinLock
{
public:
	CWinLock(CRITICAL_SECTION* pCritical)
	{
		m_pCritical = pCritical;
		EnterCriticalSection(m_pCritical);
	}
	~CWinLock()
	{
		LeaveCriticalSection(m_pCritical);
	}
private:
	CRITICAL_SECTION* m_pCritical;
};

class A
{
public:
	//把消息入到队列的线程
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 10000; ++i)
		{
			cout << "inMsgRecvQueue()执行，插入一个元素" << i << endl;
#ifdef  _WINDOWSJQ_
			//EnterCriticalSection(&my_winsec);
			CWinLock wlock(&my_winsec);
			msgRecvQueue.push_back(i);
			//LeaveCriticalSection(&my_winsec);
#else
			my_mutex.lock();
			msgRecvQueue.push_back(i);
			my_mutex.unlock();
#endif
		}
	}

	bool outMsgLULProc(int& command)
	{
#ifdef  _WINDOWSJQ_
		EnterCriticalSection(&my_winsec);
		if (!msgRecvQueue.empty())
		{
			int command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			LeaveCriticalSection(&my_winsec);
			return true;
		}
		LeaveCriticalSection(&my_winsec);
#else
		my_mutex.lock();
		if (!msgRecvQueue.empty())
		{
			int command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			my_mutex.unlock();
			return true;
		}
		my_mutex.unlock();
#endif
		return false;
	}

	A()
	{
#ifdef _WINDOWSJQ_
		InitializeCriticalSection(&my_winsec);	//用临界区之前先初始化
#endif
	}

private:
	list<int> msgRecvQueue;
	//mutex my_mutex;	//创建独占互斥量
	recursive_mutex my_mutex;//递归独占互斥量

#ifdef _WINDOWSJQ_
	CRITICAL_SECTION my_winsec;	//windows中的临界区，非常类似于C++11中的mutex
#endif
};

int main()
{
	A myobj;
	thread myOutMsgObj(&A::outMsgRecvQueue, &myobja);
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myInMsgObj.join();
	myOutMsgObj.join();
	return 0;
} 