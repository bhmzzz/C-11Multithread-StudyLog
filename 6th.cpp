#include <iostream>
#include <string>
#include <thread>
#include <list>
#include <mutex>
#include <future>
using namespace std;

//int mythread()
//{
//	cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//��ӡ���̵߳�ID
//	chrono::milliseconds dura(5000); //����һ��5s��ʱ��
//	this_thread::sleep_for(dura); //���߳���Ϣ5s
//	cout << "mythread() end" << "threadID: " << this_thread::get_id() << endl;//��ӡ���̵߳�ID
//	return 5;
//}
//int g_mycout = 0;
//atomic<int> g_mycout = 0; //���Ƿ�װ��һ������Ϊint�Ķ���
////mutex g_my_mutex;
//void mythread()//�߳���ں���
//{
//	for (int i = 0; i < 100000; ++i)
//	{
//		//g_my_mutex.lock();
//		g_mycout++; //��Ӧ�Ĳ�����һ��ԭ�Ӳ��������ᱻ���
//		//g_my_mutex.unlock();
//	}
//	return;
//}

//atomic<bool> g_ifend = false; //�߳��˳���ǣ�����ԭ�Ӳ�������ֹ����д����
//
//void mythread()
//{
//	chrono::milliseconds dura(1000); //1s
//	while (!g_ifend)
//	{
//		cout << "thread_id =" << this_thread::get_id() << "������" << endl;
//		this_thread::sleep_for(dura);
//	}
//	cout << "thread_id = " << this_thread::get_id() << "���н���" << endl;
//	return;
//}

int mythread()
{
	cout << "mythread() start" << "threadID: " << this_thread::get_id() << endl;//��ӡ���̵߳�I
	return 1;
}

int main()
{
	//cout << "main" << "threadID = " << this_thread::get_id() << endl;
	//future<int> result = async(mythread);//���̲߳��Ῠ������
	//cout << "continue...!" << endl;
	////cout << result.get() << endl; //��������ȴ�mythreadִ����ϲ����õ�����ֵ��ֻ�ܵ���һ��
	////ö������
	//future_status status = result.wait_for(chrono::seconds(1));  //�ȴ�һ��,����߳�û��ִ����ͻᳬʱ
	//if (status == future_status::timeout)
	//{
	//	//��ʱ: ��ʾ�̻߳�ûִ����
	//	cout << "��ʱ���̻߳�û��ִ����" << endl;
	//}
	//else if (status == future_status::ready)
	//{
	//	//��ʾ�̳߳ɹ�����
	//	cout << "�̳߳ɹ�ִ����ϣ�����" << endl;
	//	cout << result.get() << endl;
	//}
	//else if (status == future_status::deferred)
	//{
	//	//���async�ĵ�һ������������Ϊlaunch::defered��������ִ��
	//	cout << "�̱߳��ӳ�ִ��" << endl;
	//	cout << result.get() << endl;
	//}

	//cout << "I Love China!" << endl;
	/*thread mytobj1(mythread);
	thread mytobj2(mythread);
	mytobj1.join();
	mytobj2.join();

	//cout << "�����߳�ִ����ϣ����յĽ���ǣ�" << g_mycout << endl;*/
	//thread mytobj1(mythread);
	//thread mytobj2(mythread);
	//chrono::milliseconds dura(5000);
	//this_thread::sleep_for(dura);
	//g_ifend = true; //��ԭ�Ӷ����д���������߳��������н���
	//mytobj1.join();
	//mytobj2.join();
	//cout << "����ִ����ϣ��˳�" << endl;

	cout << "main" << "threadID = " << this_thread::get_id() << endl;
	future<int> result = async(mythread);
	cout << result.get() << endl;

	return 0;
} 