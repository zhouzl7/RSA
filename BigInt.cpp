#include"BigInt.h"

BigInt::BigInt() {
}

void BigInt::operator=(const uint num) {
	this->_data.push_back(num % BASE_VAL);
	if (num >= BASE_VAL)
		this->_data.push_back(num / BASE_VAL);
}

BigInt::BigInt(const uint num) {
	*this = num;
}

void BigInt::clear() {
	int size = this->_data.size();
	for (int i = size - 1; i > 0; i--) {
		if (this->_data[i] > 0)
			break;
		this->_data.pop_back();
	}
}

bool BigInt::checkStr(const string& str) {
	int len = str.length();
	for (int i = 0; i < len; i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

void BigInt::operator=(const string& str) {
	if (!checkStr(str)) {
		throw "please input valid string that only allow '0'-'9'.";
	}
	int len = str.length();
	while (len >= BASE_LEN) {
		this->_data.push_back(stoi(str.substr(len - BASE_LEN, BASE_LEN)));
		len = len - BASE_LEN;
	}
	if (len > 0) {
		this->_data.push_back(stoi(str.substr(0, len)));
	}
	this->clear();
}

BigInt::BigInt(const string& str) {
	*this = str;
}

int BigInt::compare(const BigInt& other) const {
	int size1 = this->_data.size();
	int size2 = other._data.size();
	
	if (size1 > size2)
		return 1;
	else if (size1 < size2)
		return -1;
	else {
		for (int i = size1 - 1; i >= 0; i--) {
			if (this->_data[i] > other._data[i])
				return 1;
			else if (this->_data[i] < other._data[i])
				return -1;
		}
		return 0;
	}
}

bool BigInt::operator==(const BigInt& other) const {
	return this->compare(other) == 0;
}

bool BigInt::operator!=(const BigInt& other) const {
	return this->compare(other) != 0;
}

bool BigInt::operator>(const BigInt& other) const {
	return this->compare(other) > 0;
}

bool BigInt::operator<(const BigInt& other) const {
	return this->compare(other) < 0;
}

bool BigInt::operator>=(const BigInt& other) const {
	return this->compare(other) >= 0;
}

bool BigInt::operator<=(const BigInt& other) const {
	return this->compare(other) <= 0;
}

string BigInt::toString() const {
	int size = this->_data.size();
	string result = to_string(this->_data[size-1]);
	for (int i = size - 2; i >= 0; i--) {
		char str[10];
		sprintf_s(str, FORMAT_STR, this->_data[i]);
		result = result + str;
	}
	return result;
}

BigInt BigInt::operator+(const BigInt& other) const {
	int size1 = this->_data.size();
	int size2 = other._data.size();
	if (size1 < size2)
		return other.operator+(*this); //确保大Size数加小Size数

	uint sum = 0;
	uint carry = 0;
	BigInt result;

	for (int i = 0; i < size2; i++) {
		sum = this->_data[i] + other._data[i] + carry;
		if (sum >= BASE_VAL) {
			result._data.push_back(sum - BASE_VAL);
			carry = 1;
		}
		else {
			result._data.push_back(sum);
			carry = 0;
		}
	}
	int ind;
	for (ind = size2; ind < size1; ind++) {
		sum = this->_data[ind] + carry;
		if (sum >= BASE_VAL) {
			result._data.push_back(sum - BASE_VAL);
			carry = 1;
		}
		else {
			result._data.push_back(sum);
			carry = 0;
			break;
		}
	}
	for (ind = ind + 1; ind < size1; ind++)
		result._data.push_back(this->_data[ind]);
	if (carry > 0) {
		result._data.push_back(carry);
	}
	return result;
}

BigInt BigInt::operator-(const BigInt& other) const {
	// 假定 other 是较小数
	/*if (*this <= other)
		return BigInt(0);*/
	int size1 = this->_data.size();
	int size2 = other._data.size();

	uint diff = 0;
	uint carry = 0;
	BigInt result;

	for (int i = 0; i < size2; i++) {
		if (this->_data[i] < other._data[i] + carry) {
			diff = this->_data[i] + BASE_VAL - carry - other._data[i];
			carry = 1;
		}
		else {
			diff = this->_data[i] - carry - other._data[i];
			carry = 0;
		}
		result._data.push_back(diff);
	}
	int ind;
	for (ind = size2; ind < size1; ind++) {
		if (this->_data[ind] < carry) {
			diff = this->_data[ind] + BASE_VAL - carry;
			carry = 1;
			result._data.push_back(diff);
		}
		else {
			diff = this->_data[ind] - carry;
			carry = 0;
			result._data.push_back(diff);
			break;
		}
	}
	for (ind = ind+1; ind < size1; ind++)
		result._data.push_back(this->_data[ind]);

	result.clear();
	return result;
}

BigInt BigInt::operator*(const BigInt& other) const {
	int size1 = this->_data.size();
	int size2 = other._data.size();
	if (size1 < size2)
		return other.operator*(*this); //确保大Size数乘小Size数

	uint64 prod = 0;
	uint carry = 0;
	BigInt result;
	BigInt temp;

	for (int i = 0; i < size2; i++) {
		temp._data.clear();
		carry = 0;

		for (int tempInd = 0; tempInd < i; tempInd++)
			temp._data.push_back(0);

		for (int j = 0; j < size1; j++) {
			prod = (uint64)(other._data[i]) * (uint64)(this->_data[j]) + carry;
			temp._data.push_back((uint)(prod % BASE_VAL));
			carry = prod / BASE_VAL;
		}
		if (carry)
			temp._data.push_back((uint)(carry));
		result = result + temp;
	}
	return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
	//假设除数一定合法
	//假设被除数一定大于除数
	/*if (*this < other)
		return BigInt(0);*/

	int size1 = this->_data.size();
	int size2 = other._data.size();

	uint quot = 0;
	BigInt result;
	BigInt temp;

	for (int i = size1 - size2 + 1; i < size1; i++) {
		temp._data.push_back(this->_data[i]);
	}
	for (int i = size1 - size2; i >= 0; i--) {
		temp._data.insert(temp._data.begin(), this->_data[i]);
		temp.clear();
		quot = getMaxCycle(temp, other);
		temp = temp - other * quot;
		result._data.insert(result._data.begin(), quot);
	}
	result.clear();
	return result;
}

uint BigInt::getMaxCycle(const BigInt& a, const BigInt& b) {
	BigInt tempA = a;
	BigInt tempB = b;
	uint temp;
	uint result = 0;
	bool flag = true;

	while(tempA >= tempB) {
		temp = estimateQuotient(tempA, tempB);
		tempA = tempB * temp - tempA;
		result = flag ? (result + temp) : (result - temp);
		flag = !flag;
	}
	while (result > 0 && (tempB * result) > a)
		result--;
	return result;
}

uint BigInt::estimateQuotient(const BigInt& a, const BigInt& b) {
	int sizeA = a._data.size();
	int sizeB = b._data.size();
	uint64 valA, valB;
	if (sizeA == sizeB) {
		if (sizeA > 1) {
			valA = (uint64)a._data[sizeA - 1] * BASE_VAL + a._data[sizeA - 2];
			valB = (uint64)b._data[sizeB - 1] * BASE_VAL + b._data[sizeB - 2];
		}
		else {
			valA = (uint64)a._data[sizeA - 1];
			valB = (uint64)b._data[sizeB - 1];
		}
	}
	else {
		valA = (uint64)a._data[sizeA - 1] * BASE_VAL + a._data[sizeA - 2];
		valB = (uint64)b._data[sizeB - 1];
	}
	return (uint)(valA / valB);
}