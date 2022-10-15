#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>
using namespace std;

//class A
//{
//public:
//	int mythread(int mypar)
//	{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//		chrono::milliseconds dura(5000); //定义一个5s的时延
//		this_thread::sleep_for(dura); //该线程休息5s
//		cout << "mythread() end" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//		return 5;
//	}
//};


//int mythread(int mypar)
//	{
//		cout << mypar << endl;
//		cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//		chrono::milliseconds dura(5000); //定义一个5s的时延
//		this_thread::sleep_for(dura); //该线程休息5s
//		cout << "mythread() end" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
//		return 5;
//	}
//
//vector<packaged_task<int(int)> > mytask;

void mythread(promise<int>& temp,int calc)
{
	calc++;
	calc *= 10;
	chrono::milliseconds dura(5000); //定义一个5s的时延
	this_thread::sleep_for(dura); //该线程休息5s

	int result = calc;
	temp.set_value(result);	//结果保存到了temp对象中

	return;
}

void mythread2(future<int>& tmpf)
{
	auto result = tmpf.get();
	cout << "mythread2 result:" << result << endl;
	return;
}

int main()
{
	////一：std::async(异步)、std::future创建后台任务并返回值
	////希望线程返回一个结果;
	//A a;
	//int tmppar = 12;

	//cout << "main" << "threadID = " << this_thread::get_id() << endl;
	////future<int> result = async(mythread,tmppar);//主线程不会卡在这里
	//future<int> result = async(launch::async,&A::mythread,&a, tmppar);//第二个参数是一个对象this指针保证线程里用的是同一个对象
	//cout << "continue...!" << endl;
	//int def;
	//def = 0;
	//cout << result.get() << endl; //卡在这里等待mythread执行完毕才能拿到返回值，只能调用一次
	////result.wait();
	//cout << "I Love China!" << endl;

	//cout << "main" << "threadID = " << this_thread::get_id() << endl;

	////packaged_task<int(int)> mypt(mythread); //我们把函数mythread通过packaged_task包装起来

	//packaged_task<int(int)> mypt([](int mypar) ->int {
	//	cout << mypar << endl;
	//	cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
	//	chrono::milliseconds dura(5000); //定义一个5s的时延
	//	this_thread::sleep_for(dura); //该线程休息5s
	//	cout << "mythread() end" << "threadID: " << this_thread::get_id() << endl;//打印新线程的ID
	//	return 5;
	//	});

	//thread t1(ref(mypt), 1);	//线程开始执行，第二个参数作为线程入口函数的参数
	//t1.join();	//等待线程执行完毕
	//future<int> result = mypt.get_future();	//保存mythread返回结果
	//cout << result.get() << endl;
	//cout << "I Love China!" << endl;
	//mypt(105);	//直接调用相当于函数调用。
	//future<int> result = mypt.get_future();
	//cout << result.get() << endl;

	//mytask.push_back(move(mypt));	//入容器，移动语义,mypt就为空

	//packaged_task<int(int)> mypt2;
	//auto iter = mytask.begin();
	//mypt2 = move(*iter);	//移动语义
	//mytask.erase(iter);		//删除第一个元素，迭代器失效，后续代码不可以再使用iter
	//mypt2(123);
	//future<int> result = mypt2.get_future();
	//cout << result.get() << endl;

	promise<int> myprom; //声明该对象保存的值类型为int
	thread t1(mythread, ref(myprom), 180);
	t1.join();

	//获取结果值
	future<int> fu1 = myprom.get_future();	//promise和future绑定用于获取线程返回值
	//auto result = fu1.get();	//get只能调用一次
	//cout << result << endl;
	thread t2(mythread2, ref(fu1));
	t2.join(); //等mythread2线程执行完毕



	cout << "I Love China!" << endl;
	//通过promise保存一个值，在将来某个时刻我们通过把一个future绑定到这个promise上来得到这个绑定的值

	return 0;
}