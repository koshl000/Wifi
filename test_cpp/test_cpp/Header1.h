#pragma once
#include "Header.h"
#include<iostream>
class B {

public:

	B() { a = new A(*this); }

	void foo()

	{

		std::cout << "test";

	}

	A *a;

};