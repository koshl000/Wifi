#include "Pointer.h"
template<typename T>
inline Pointer<T>::Pointer(T * inPtr)
{
	mPtr = inPtr;
}

template<typename T>
inline Pointer<T>::~Pointer()
{
	delete mPtr;
	mPtr = nullptr;
}

template<typename T>
inline T & Pointer<T>::operator*()
{
	return *mPtr;
}

template<typename T>
inline const T & Pointer<T>::operator*() const
{
	return *mPtr;
}

template<typename T>
inline T * Pointer<T>::operator->()
{
	return mPtr;
}

template<typename T>
inline const T * Pointer<T>::operator->() const
{
	return mPtr;
}
