#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;

typedef unsigned int uint;
typedef unsigned long long uint64;

#define BASE_VAL 1000000000
#define BASE_LEN 9
#define FORMAT_STR "%09d"

class BigInt {
private:
	vector<uint> _data;

	void clear();
	bool checkStr(const string& str);
	int compare(const BigInt& other) const;
	static uint estimateQuotient(const BigInt& a, const BigInt& b);
	static uint getMaxCycle(const BigInt& a, const BigInt& b);
public:
	BigInt();
	BigInt(const uint num);
	BigInt(const string& str);

	// 赋值
	void operator=(const uint num);
	void operator=(const string& str);

	//比较运算符
	bool operator==(const BigInt& other) const;
	bool operator!=(const BigInt& other) const;
	bool operator>(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
	bool operator>=(const BigInt& other) const;
	bool operator<=(const BigInt& other) const;

	// 四则运算符
	BigInt operator+(const BigInt& other) const;
	BigInt operator-(const BigInt& other) const;
	BigInt operator*(const BigInt& other) const;
	BigInt operator/(const BigInt& other) const;

	string toString() const;
};