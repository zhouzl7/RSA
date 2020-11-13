#include "RSA.h"
#include <ctime>
#include <sstream>

RSA::RSA()
{
	this->e = 65537;
}

void RSA::init(uint n)
{
	srand(time(NULL));
	this->p = generatePrime(n/2, 5);
	this->q = generatePrime(n/2, 5);
	this->N = p * q;
	this->phiN = (p - 1) * (q - 1);
	this->generatePrivateKey();
}

BigInt RSA::generatePrime(const uint n, int count)
{
	BigInt result = this->generateOdd(n);
	while (!isPrime(result, count)) {
		result = result + 2;
	}
	return result;
}

BigInt RSA::generateOdd(const uint n)
{
	char decimal_table[] = { '0','1','2','3','4','5','6','7','8','9' };
	ostringstream oss;
	for (uint i = 0; i < n - 1; i++)
		oss << decimal_table[rand() % 10];
	oss << '1';
	string str(oss.str());
	return BigInt(str);
}

BigInt RSA::generateRand(const BigInt n)
{
	uint t = 0;
	while (t == 0) {
		t = rand();
	}
	BigInt result = BigInt(t) % n;
	if (result == 0)
		result = n - 1;
	return result;
}

BigInt RSA::modular_exp(BigInt a, BigInt e, const BigInt n)
{
	a = a % n;
	BigInt result(1);
	while (e != 0) {
		if (e % 2 == 1) {
			//result = (result % n) * (a % n);
			result = result % n;
			BigInt temp = a % n;
			result = result * temp;
		}
		//a = (a * a) % n;
		a = a % n;
		a = a * a;
		e = e / 2;
	}
	return result;
}

bool RSA::isPrime(const BigInt& n, const uint k)
{
	if (n == BigInt(2))
		return true;
	BigInt n_1 = n - 1;
	BigInt M = n_1 / 2;
	uint r = 1;
	if (M % 2 == 0)
		return false; //令随机数的 r = 1，则可以省去Miller-Rabbin二次探测的循环
	for (uint i = 0; i < k; i++) {
		BigInt a = this->generateRand(n_1);
		BigInt moden1 = this->modular_exp(a, M, n);
		if (moden1 != 1 && moden1 != n_1)
			return false;
	}
	return true;
}

void RSA::generatePrivateKey()
{
	this->d = BigInt();
}
