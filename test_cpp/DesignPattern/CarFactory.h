#pragma once
#include "Car.h"
class CarFactory
{
public:
	CarFactory();
	Car* requestCar();
	int getNumCarsInProduction() const;
protected:
	virtual Car* createCar() = 0;
private:
	int mNumCarsInProduction;
};
class FordFactory :public CarFactory
{
protected:
	virtual Car* createCar();
};
class AudiFactory :public CarFactory
{
protected:
	virtual Car* createCar();
};