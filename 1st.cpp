#include "head.h"
#include <thread>
#include <algorithm>
#include <string>
#include <list>
#include <mutex>
using namespace std;

mutex resource_mutex;
once_flag g_flag; //���Ǹ�ϵͳ����ı��



class MyCAS
{
	static void CreateInstance() //ֻ������һ��
	{
		chrono::milliseconds dura(20000);//�ȴ�20s
		this_thread::sleep_for(dura);

		m_instance = new MyCAS();
		static MyGC gc;
	}
private:
	MyCAS() {};//˽�л��Ĺ��캯��
private:
	static MyCAS* m_instance;
public:
	static MyCAS* GetInstance()
	{
		//if (m_instance == nullptr)//˫��������˫�ؼ�飩���Ч�� 
		//{
		//	unique_lock<mutex> mymutex(resource_mutex);//�Զ�����������
		//	if (m_instance == nullptr)
		//	{
		//		m_instance = new MyCAS();
		//		static MyGC gc;
		//	}
		//}
		call_once(g_flag, CreateInstance); //�����߳�ͬʱִ�е��������һ���߳�Ҫ�ȴ���һ���߳�ִ�����CreateInstance������ж��Ƿ����ִ�С�
		cout << "call_once()ִ�����" << endl;
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
		cout << "����" << endl;
	}
	~MyCAS()
	{
		cout << "����ִ��" << endl;
	}
};

MyCAS* MyCAS::m_instance = nullptr;

void mythread()
{
	cout << "�ҵ��߳̿�ʼִ��" << endl;
	MyCAS* p_a = MyCAS::GetInstance();
	cout << "�ҵ��߳�ִ�����" << endl;
	return;
}
int main() {
	thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();
   return 0;
}
