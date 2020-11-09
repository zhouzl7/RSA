#include<iostream>
#include<ctime>
#include"BigInt.h"
using namespace std;

int main()
{
	BigInt a, b, c;
	try {
		a = "100000000000000000050000008923456789000000000123453";
		b = "990000000000000000000000000892345678900000100012345";
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	cout << a.toString() << endl;
	cout << b.toString() << endl;
	cout << (b*a).toString() << endl;
}