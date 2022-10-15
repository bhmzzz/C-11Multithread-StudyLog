#include<iostream>
#include<stack>
#include<vector>
#include<cstdlib>
#include<thread>
#include<mutex>
#include<list>
using namespace std;

class A {
public:
	void inMsgRecvQueue()
	{
		for (int i = 0; i < 100000; ++i)
		{
			cout << "执行，插入一个元素" << i << endl;
			unique_lock<mutex> sbguard1(my_mutex1);
			msgRecvQueue.push_back(i);
			my_cond.notify_one();	//通知另一个线程，把wait()唤醒。
		}
		return;
	}

	/*bool outMsgLULProc(int& command)
	{
		unique_lock<mutex> sbguard1(my_mutex1);

		if (!msgRecvQueue.empty())
		{
			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			return true;
		}
		return false;
	}*/

	void outMsgRecvQueue()
	{
		int command = 0;
		while (true)
		{
			unique_lock<mutex> sbguard1(my_mutex1);
			my_cond.wait(sbguard1, [this] {
				if (!msgRecvQueue.empty())
					return true;
				return false;
				});

			command = msgRecvQueue.front();
			msgRecvQueue.pop_front();
			sbguard1.unlock();  //因为unique_lock的灵活性，所以我们可以随时unlock以免锁住太长。
			cout << "outMsgRecvQueue()执行，取出元素" << endl;
		}

		/*for (int i = 0; i < 100000; ++i)
		{
			bool result = outMsgLULProc(command);
			if (result)
			{
				cout << "outMsgRecvQueue()执行，取出一个元素" << command << endl;
			}
			else
			{
				cout << "outMsgRecvQueue()执行，但目前消息队列中为空" << i << endl;
			}
		}
		cout << "end" << endl;*/
	}

private:
	list<int> msgRecvQueue;
	mutex my_mutex1;
	condition_variable my_cond; //生成一个条件对象
};

int main()
{

	A myobja;
	thread myOutnMsgObj(&A::outMsgRecvQueue, &myobja);
	thread myInMsgObj(&A::inMsgRecvQueue, &myobja);
	myOutnMsgObj.join();
	myInMsgObj.join();
	return 0;
}
