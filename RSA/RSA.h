#pragma once
#include "BigInt.h"

class RSA {
public:
	BigInt e; //ָ��
	BigInt N; //��Կ

public:
	BigInt d; //˽Կ
	BigInt p; //����p
	BigInt q; //����q
	BigInt phiN; //ŷ����

public:
	RSA();
	void init(uint n); //��ʼ������������Ϊn�Ĺ�˽Կ

	BigInt encrypt(const BigInt& plaintext);
	BigInt decrypt(const BigInt& ciphertext);

public:
	BigInt generatePrime(const uint n, int count); //���ɳ���Ϊn���������
	BigInt generateOdd(const uint n); //���ɳ���Ϊn������
	BigInt generateRand(const BigInt n); //����С��n�������
	BigInt modular_exp(BigInt a, BigInt e, const BigInt n); //��ģ����
	BigInt extendEuclid(const BigInt e, const BigInt n); //��չŷ������㷨
	bool isPrime(const BigInt& n, const uint k); //�����ж�
	void generatePrivateKey(); //����˽Կ
};