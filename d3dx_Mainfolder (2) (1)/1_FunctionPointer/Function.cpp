#include <iostream>
using namespace std;

template<typename T>
void Print(T data)
{
	cout << "�Ϲ� �Լ� : " << data << endl;
}

template<>
void Print(float data)
{
	cout << "Ư��ȭ �Լ� : " << data << endl;
}

template<typename T>
void Print(T* data)
{
	cout << "������ �Լ� : " << *data << endl;
}

//void main()
//{
//	int i = 10;
//	Print(i);
//	//Print<int>(i);
//
//	float j = 20.0f;
//	Print(j);
//
//	double k = 30.0;
//	Print(k);
//
//	int* p = &i;
//	Print<int>(p);
//}