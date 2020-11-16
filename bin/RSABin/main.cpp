#include <iostream>
#include <ctime>
#include <cassert>
#include <ctime>
#include "BigInt.h"
#include "RSA.h"
using namespace std;

void my_assert() {
	assert((BigInt("28764535259006346816")
		/ BigInt("6492216783")).toString() ==
		"4430618419");
	assert((BigInt("28764535259006346816")
		% BigInt("6492216783")).toString() ==
		"105620739");

	assert((BigInt("8075754516126350259")
		/ BigInt("8142539583")).toString() ==
		"991798005");
	assert((BigInt("8075754516126350259")
		% BigInt("8142539583")).toString() ==
		"2073418344");

	assert((BigInt("1285488099737592976")
		/ BigInt("9361513271")).toString() ==
		"137316271");
	assert((BigInt("1285488099737592976")
		% BigInt("9361513271")).toString() ==
		"6446860535");

	assert((BigInt("4524612452105635000008923456789005630005630000123454000023435634543200000094235100000000001234567890123000000000000000000000000000000000000000")
		/ BigInt("94325345426546543645645364564530003")).toString() ==
		"47968151419377112344541738620216963793734700353456734461333032916298200517181124373112079614797602831182104");
	assert((BigInt("4524612452105635000008923456789005630005630000123454000023435634543200000094235100000000001234567890123000000000000000000000000000000000000000")
		% BigInt("94325345426546543645645364564530003")).toString() ==
		"457067444789598341954102335333688");

	assert((BigInt("20000000000")
		/ BigInt("5000000001")).toString() ==
		"3");
	assert((BigInt("20000000000")
		% BigInt("5000000001")).toString() ==
		"4999999997");

	assert((BigInt("99999999999999999999999999999999999999999999999999999999")
		/ BigInt("123456765879856756745345")).toString() ==
		"810000159062291054558565682909300");
	assert((BigInt("99999999999999999999999999999999999999999999999999999999")
		% BigInt("123456765879856756745345")).toString() ==
		"93748044520841167791499");
	assert((BigInt("99999999999999999999999999999999999999999999999999999999000000000000000000000000000000000000")
		/ BigInt("123456765879856756745345")).toString() ==
		"810000159062291054558565682909300759359309736600892808664306658595031");
	assert((BigInt("99999999999999999999999999999999999999999999999999999999000000000000000000000000000000000000")
		% BigInt("123456765879856756745345")).toString() ==
		"27570763860170050619305");
}

int main()
{
	
	my_assert();
	BigInt a, b, c;
	a = "65537"; 
	b = "9435349541954342352345234654534536543252345343452346546543634500";
	//c = a - b;
	//cout << c.is_negative << " " << c.toString();
	//cout << a.div(b,c).toString() << endl;
	//cout << c.toString() << endl;

	RSA rsa;
	uint digits;
	cout << "请输入模N位数（十进制位数）：";
	cin >> digits;
	cout << "RSA init..." << endl;
	clock_t start = clock();
	rsa.init(digits);
	clock_t end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Total time:" << endtime * 1000 << "ms" << endl;	//ms为单位
	cout << "素数p：" << rsa.p.toString() << endl;
	cout << "素数q：" << rsa.q.toString() << endl;
	cout << "公钥N (e=65537)：" << rsa.N.toString() << endl;
	//cout << "欧拉数phiN：" << rsa.phiN.toString() << endl;
	cout << "密钥d：" << rsa.d.toString() << endl << endl;
	//cout << ((rsa.d * rsa.e) % rsa.phiN).toString() << endl << endl;

	BigInt plaintext, ciphertext;
	string str;
	cout << "请输入明文（10进制数字串）：";
	cin >> str;
	plaintext = str;
	ciphertext = rsa.encrypt(plaintext);
	cout << "密文：" << ciphertext.toString() << endl << endl;
	cout << "解密：" << rsa.decrypt(ciphertext).toString() << endl << endl;
	system("pause");
}