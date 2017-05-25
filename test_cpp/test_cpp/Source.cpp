#include <iostream>
#include <stdlib.h>
#include <winsock2.h>
#include <math.h>

using namespace std;

bool range(int min,int max,int n)
{
	if (n < min || n > max)
	{
		return false;
	}
	return true;
		
}
int main(int argc, char* argv[])
{
	int n;
	int k;
	cin >> n >> k;
	while (!range(1, pow(10, 5), n))
	{
		cout << "try again.." << endl;
		cout << "n: ";
		cin >> n;
	}
	while (!range(1, pow(10, 9), k))
	{
		cout << "try again.." << endl;
		cout << "k: ";
		cin >> k;
	}

	cout << n <<' '<< k << endl;
}