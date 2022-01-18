#pragma once
#include <iostream>
#include <string>

using namespace std;

// Ham chuyen chuoi thap phan sang nhi phan
string DecToBin(string dec);

// Ham chuyen chuoi thap luc phan sang nhi phan
string HexToBin(string hex);

// Ham chuyen chuoi nhi phan sang thap phan
string BinToDec(string bin);

// Ham chuyen chuoi nhi phan sang thap luc phan
string BinToHex(string bin);

class QInt {
	long long arrayBits[2];

public:

	// --- High level method ---

		// Ham Chuyen doi QInt thong qua chuoi "base"
	string ConvertToBase(string base);

		// Ham tinh toan QInt voi operator "oper"
	void CalculateWithOperator(string oper);

		// Ham tinh toan QInt voi operator "oper" va doi so QInt x
	void CalculateWithOperator(string oper, const QInt& x);

		// Cap nhap du lieu QInt bang chuoi "data" va co so "base"
	void UpdateByBase(string base, string data);


	// --- QInt_Convert_To_Base ---

	string ToBin() const;
	string ToHex() const;
	string ToDec() const;


	// ---CALCULATE OPERATIONS---

	QInt operator+ (const QInt& b)const;

	QInt operator- (const QInt& b)const;

	QInt operator* (const QInt& b)const;

	QInt operator/ (const QInt& b)const;


	// ---COMPARING OPERATIONS---

	bool operator<  (const QInt& b)const;

	bool operator> (const QInt& b)const;

	bool operator== (const QInt& b)const;

	bool operator!= (const QInt& b)const;

	bool operator<= (const QInt& b)const;

	bool operator>= (const QInt& b)const;

	// ---BITWISE OPERATIONS---

	QInt operator& (const QInt& b);

	QInt operator| (const QInt& b);

	QInt operator^ (const QInt& b);

	void operator~ ();

	void operator<< (unsigned int n);

	void operator>> (unsigned int n);	
	
	void operator<< (const QInt& b);

	void operator>> (const QInt& b);

	void ror(unsigned int n = 1);

	void rol(unsigned int n = 1);

		// Ham bu2 cho QInt
	void TwosCompliment();


public:

	QInt& operator= (const QInt& a) {
		arrayBits[0] = a.arrayBits[0];
		arrayBits[1] = a.arrayBits[1];
		return *this;
	}

	QInt()
	{
		arrayBits[0] = arrayBits[1] = 0;

	}
	QInt(long long l1, long long l0)
	{
		arrayBits[1] = l1;
		arrayBits[0] = l0;
	}

};


