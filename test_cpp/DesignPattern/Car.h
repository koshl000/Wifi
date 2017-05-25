#pragma once
#include<iostream>
using namespace std;
class Car
{
public:
	virtual void info() = 0;
};
class Ford :public Car
{
public:
	virtual void info() { cout << "Ford" << endl; }
};
class Audi :public Car
{
public:
	virtual void info() { cout << "Audi" << endl; }
};

 