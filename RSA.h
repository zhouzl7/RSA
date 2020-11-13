#pragma once
#include "BigInt.h"

class RSA {
public:
	BigInt e; //指数
	BigInt N; //公钥

public:
	BigInt d; //私钥
	BigInt p; //素数p
	BigInt q; //素数q
	BigInt phiN; //欧拉数

public:
	RSA();
	void init(uint n); //初始化，产生长度为n的公私钥

public:
	BigInt generatePrime(const uint n, int count); //生成长度为n的随机素数
	BigInt generateOdd(const uint n); //生成长度为n的奇数
	BigInt generateRand(const BigInt n); //生成小于n的随机数
	BigInt modular_exp(BigInt a, BigInt e, const BigInt n);
	bool isPrime(const BigInt& n, const uint k); //素数判断
	void generatePrivateKey(); //生成私钥
};