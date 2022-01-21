#include <iostream>
#include <string>
#include "Template.h"
using namespace std;

template<typename T>
class Character
{
public:
	void Set(T name)
	{
		this->name = name;
	}

	void Print()
	{
		cout << "Ä³¸¯ÅÍ : " << name << endl;
	}

private:
	T name;
};

//void main()
//{
//	float a = 10;
//	float b = 20;
//	swap(a, b);
//	string one = "one";
//	string two = "two";
//	swap(one, two);
//
//	
//
//	//Character<int> ob;
//	//ob.Set(20);
//	//ob.Print();
//
//	//Character<string> obs;
//	//obs.Set("Oak");
//	//obs.Print();
//
//	Template<string> myStringTemp("StringType");
//	string temp = myStringTemp.GetName();
//	cout << temp << endl;
//	Template<int> myIntTemp(12345);
//	auto temp2 = myIntTemp.GetName();
//
//	myStringTemp = myIntTemp;
//
//
//
//}