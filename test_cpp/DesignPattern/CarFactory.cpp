#include "CarFactory.h"

CarFactory::CarFactory() :mNumCarsInProduction(0){}
Car* CarFactory::requestCar()
{
	mNumCarsInProduction++;
	return createCar();
}

Car * FordFactory::createCar()
{
	return new Ford();
}

Car * AudiFactory::createCar()
{
	return new Audi();
}
