#include "head.h"
#include <thread>
#include <algorithm>
#include <string>
#include <list>
#include <mutex>
using namespace std;

mutex resource_mutex;
once_flag g_flag; //这是个系统定义的标记



class MyCAS
{
	static void CreateInstance() //只被调用一次
	{
		chrono::milliseconds dura(20000);//等待20s
		this_thread::sleep_for(dura);

		m_instance = new MyCAS();
		static MyGC gc;
	}
private:
	MyCAS() {};//私有化的构造函数
private:
	static MyCAS* m_instance;
public:
	static MyCAS* GetInstance()
	{
		//if (m_instance == nullptr)//双重锁定（双重检查）提高效率 
		//{
		//	unique_lock<mutex> mymutex(resource_mutex);//自动加锁，解锁
		//	if (m_instance == nullptr)
		//	{
		//		m_instance = new MyCAS();
		//		static MyGC gc;
		//	}
		//}
		call_once(g_flag, CreateInstance); //两个线程同时执行到这里，其中一个线程要等待另一个线程执行完毕CreateInstance后才能判断是否继续执行。
		cout << "call_once()执行完毕" << endl;
		return m_instance;
	}
	class MyGC {
	public:
		~MyGC()
		{
			if (MyCAS::m_instance)
			{
				delete MyCAS::m_instance;
				MyCAS::m_instance = nullptr; 
			}
		}
	};

	void func()
	{
		cout << "测试" << endl;
	}
	~MyCAS()
	{
		cout << "析构执行" << endl;
	}
};

MyCAS* MyCAS::m_instance = nullptr;

void mythread()
{
	cout << "我的线程开始执行" << endl;
	MyCAS* p_a = MyCAS::GetInstance();
	cout << "我的线程执行完毕" << endl;
	return;
}
int main() {
	thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
   return 0;
}
