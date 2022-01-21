#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Template
{
public:
	Template(T name);

	//Template(const Template<T>& src);

	template<typename E>
	Template(const Template<E>& src);

	//Template<T>& operator=(const Template<T>& rhs);
	template<typename E>
	Template<T>& operator=(const Template<E>& rhs);

	~Template();

	T& GetName() { return name; }

	//void copyFrom(const Template<T>& src);

	template <typename E>
	void copyFrom(const Template<T>& src);

private:
	T name;

};

template<typename T>
inline Template<T>::Template(T name)
	:name(name)
{

}

//template<typename T>
//inline Template<T>::Template(const Template<T>& src)
//{
//	copyFrom(src);
//}

//template<typename T>
//inline Template<T>& Template<T>::operator=(const Template<T>& rhs)
//{
//	copyFrom(rhs);
//}

template<typename T>
inline Template<T>::~Template()
{
}

//template<typename T>
//inline void Template<T>::copyFrom(const Template<T>& src)
//{
//	name = src.name;
//}

template<typename T>
template<typename E>
inline Template<T>::Template(const Template<E>& src)
{
	copyFrom(src);
}

template<typename T>
template<typename E>
inline Template<T>& Template<T>::operator=(const Template<E>& rhs)
{
	copyFrom(src);
}

template<typename T>
template<typename E>
inline void Template<T>::copyFrom(const Template<T>& src)
{
	name = src.name;
}

/////////////////////////////////////////////
template<>
class Template<float>
{

};