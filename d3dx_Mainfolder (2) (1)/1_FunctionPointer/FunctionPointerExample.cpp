#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

static void Idle()
{
	cout << "���" << endl;
}
void Move()
{
	cout << "�̵�" << endl;
}
void Attack()
{
	cout << "����" << endl;
}

void Behavior(void(*bp2)())
{
	for (int i = 0; i < 10; i++)
		cout << i;
	cout << endl;
	bp2();
}

int main()
{
	//�⺻���� �Լ�������
	//int behavior = 0;

	//void(*bp[3])();
	//bp[0] = Idle;
	//bp[1] = Move;
	//bp[2] = Attack;

	//bp[behavior]();

	//-------------------

	//�Լ��� �̿��� �Լ�������
	/*void(*bp)() = Attack;
	Behavior(bp);*/
	function<void()> func = bind(Idle);

	func();

	function<string(int, int)> func2;


}