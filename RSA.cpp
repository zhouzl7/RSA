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

BigInt RSA::encrypt(const BigInt& plaintext)
{
	return this->modular_exp(plaintext, this->e, this->N);
}

BigInt RSA::decrypt(const BigInt& ciphertext)
{
	return this->modular_exp(ciphertext, this->d, this->N);
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
	oss << decimal_table[(rand() % 9) + 1];
	for (uint i = 0; i < n - 2; i++)
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
			result = (result * a) % n;
		}
		a = (a * a) % n;
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

BigInt RSA::extendEuclid(const BigInt e, const BigInt n)
{
	BigInt r0 = n;
	BigInt r1 = e;
	BigInt t0(0);
	BigInt t1(1);
	BigInt t;

	while (r1 != 0) {
		BigInt r;
		BigInt p = r0.div(r1, r);
		BigInt tmp = p * t1;
		while (tmp > t0)
			t0 = t0 + n;
		t = t0 - tmp;
		r0 = r1;
		r1 = r;
		t0 = t1;
		t1 = t;
	}
	return t0;

	/*BigInt a[3], b[3], t[3];
	a[0] = 1; a[1] = 0; a[2] = n;
	b[0] = 0; b[1] = 1; b[2] = e;
	if (b[2] == 0 || b[2] == 1) {
		return b[2];
	}

	while (true) {
		if (b[2] == 1) {
			return b[1];
		}

		BigInt q = a[2] / b[2];
		for (int i = 0; i < 3; i++) {
			t[i] = a[i] - q * b[i];
			a[i] = b[i];
			b[i] = t[i];
		}
	}*/
}

void RSA::generatePrivateKey()
{
	this->d = this->extendEuclid(this->e, this->phiN);
}
