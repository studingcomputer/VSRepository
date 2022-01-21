#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <functional>
using namespace std;

static void Idle()
{
	cout << "대기" << endl;
}
void Move()
{
	cout << "이동" << endl;
}
void Attack()
{
	cout << "공격" << endl;
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
	//기본적인 함수포인터
	//int behavior = 0;

	//void(*bp[3])();
	//bp[0] = Idle;
	//bp[1] = Move;
	//bp[2] = Attack;

	//bp[behavior]();

	//-------------------

	//함수를 이용한 함수포인터
	/*void(*bp)() = Attack;
	Behavior(bp);*/
	function<void()> func = bind(Idle);

	func();

	function<string(int, int)> func2;


}