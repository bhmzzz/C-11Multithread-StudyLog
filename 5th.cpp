#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>
using namespace std;

//int mythread()
//{
//	cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//	chrono::milliseconds dura(5000); //定义一个5s的时延
//	this_thread::sleep_for(dura); //该线程休息5s
//	cout << "mythread() end" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//	return 5;
//}
//int g_mycout = 0;
//atomic<int> g_mycout = 0; //我们封装了一个类型为int的对象
////mutex g_my_mutex;
//void mythread()//线程入口函数
//{
//	for (int i = 0; i < 100000; ++i)
//	{
//		//g_my_mutex.lock();
//		g_mycout++; //对应的操作是一个原子操作，不会被打断
//		//g_my_mutex.unlock();
//	}
//	return;
//}

atomic<bool> g_ifend = false; //线程退出标记，这是原子操作，防止读和写乱套

void mythread()
{
	chrono::milliseconds dura(1000); //1s
	while (!g_ifend)
	{
		cout << "thread_id =" << this_thread::get_id() << "运行中" << endl;
		this_thread::sleep_for(dura);
	}
	cout << "thread_id = " << this_thread::get_id() << "运行结束" << endl;
	return;
}

int main()
{
	//cout << "main" << "threadID = " << this_thread::get_id() << endl;
	//future<int> result = async(mythread);//主线程不会卡在这里
	//cout << "continue...!" << endl;
	////cout << result.get() << endl; //卡在这里等待mythread执行完毕才能拿到返回值，只能调用一次
	////枚举类型
	//future_status status = result.wait_for(chrono::seconds(1));  //等待一秒,如果线程没有执行完就会超时
	//if (status == future_status::timeout)
	//{
	//	//超时: 表示线程还没执行完
	//	cout << "超时，线程还没有执行完" << endl;
	//}
	//else if (status == future_status::ready)
	//{
	//	//表示线程成功返回
	//	cout << "线程成功执行完毕，返回" << endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == future_status::deferred)
	//{
	//	//如果async的第一个参数被设置为launch::defered，则本条件执行
	//	cout << "线程被延迟执行" << endl;
	//	cout << result.get() << endl;
	//}

	//cout << "I Love China!" << endl;
	/*thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();

	cout << "两个线程执行完毕，最终的结果是：" << g_mycout << endl;*/
	thread mytobj1(mythread);
	thread mytobj2(mythread);
	chrono::milliseconds dura(5000);
	this_thread::sleep_for(dura);
	g_ifend = true; //对原子对象的写操作，让线程自行运行结束
	mytobj1.join();
	mytobj2.join();
	cout << "程序执行完毕，退出" << endl;


	return 0;
} 