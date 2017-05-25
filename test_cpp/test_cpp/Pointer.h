#pragma once
template<typename T>
class Pointer
{
public:
	Pointer(T* inPtr);
	virtual ~Pointer();
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
protected:
	T* mPtr;
private:
	Pointer(const Pointer<T>& src);
	Pointer<T>& operator=(const Pointer<T>& src);
};

#include "Pointer.hpp"

