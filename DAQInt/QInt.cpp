#include "QInt.h"
#include <map>

//==================== String method definition =======================

#pragma region String_Math

	//Ham xoa ky tu '0' dau tien
void deleteFirstZeroChar(string& s) {
	while (s[0] == '0')
	{
		s.erase(0, 1);
	}
}

// Ham chia 2 chuoi thap phan duong
void DividedBy2(string& dec)
{
	int temp;
	bool remainder = false;	// phan du khi chia cho 2

	int len = dec.length();
	for (int i = 0; i < len; i++)
	{
		temp = ((dec[i] - 48) + remainder * 10) / 2 + 48;

		if (dec[i] % 2 != 0) remainder = true;
		else remainder = false;

		dec[i] = temp;
	}
	deleteFirstZeroChar(dec);
}

// Ham dao nguoc chuoi
string ReverseString(string s) {
	return string(s.rbegin(), s.rend());
}

// Ham cong 2 chuoi thap phan
string PlusDecString(string dec, string dec2) {
	string result;

	dec = ReverseString(dec);
	dec2 = ReverseString(dec2);

	int len;
	if (dec.length() > dec2.length()) {
		len = dec.length();
		dec2.resize(len, '0');
	}
	else {
		len = dec2.length();
		dec.resize(len, '0');
	}

	bool remainder = false;
	int c;
	for (int i = 0; i < len; i++)
	{
		// p/s: c = (dec[i] - 48) + (dec2[i] - 48) + 48;
		c = dec[i] - 48 + dec2[i] + remainder;
		remainder = false;
		if (c > '9') {
			remainder = true;
			c -= 10;
		}
		result.insert(result.end(), c);
	}
	if (remainder) {
		result.insert(result.end(), '1');
	}
	result = ReverseString(result);
	return result;
}

// Ham nhan 2 chuoi thap phan
string MultipleDecString(string dec, string dec2) {
	string result;

	dec = ReverseString(dec);
	dec2 = ReverseString(dec2);

	int len = dec.length(), len2 = dec2.length();

	string temp;
	// nhan tung chu so va cong lai dua tren so mu bac 10
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			// c = (dec[i] - 48) + (dec2[i] - 48) + 48;
			temp = to_string((dec[i] - 48) * (dec2[j] - 48));
			temp.resize(temp.length() + i + j, '0');
			result = PlusDecString(result, temp);
		}
	}
	return result;
}

#pragma endregion


#pragma region Convert_String_By_Base

// Ham chuyen chuoi nhi phan sang thap phan
string BinToDec(string bin)
{
	// chuyen nhi phan sang thap phan theo cach thong thuong
	string dec = "0";
	int len = bin.length();
	for (int i = 0; i < len; i++)
	{
		dec = MultipleDecString(dec, "2");
		dec = PlusDecString(dec, string(1, bin[i]));
	}
	return dec;
}

// Ham chuyen chuoi nhi phan sang thap luc phan
string BinToHex(string bin)
{
	string Bin_Hex[2][2][2][2] = {
		{
			{
				{"0","1"},
				{"2","3"}
			},
			{
				{"4","5"},
				{"6","7"}
			},
		},
		{
			{
				{"8","9"},
				{"A","B"}
			},
			{
				{"C","D"},
				{"E","F"}
			},
		}
	};


	string hex = "";

	// Dam bao chuoi nhi phan co do dai chia het cho 4
	int offset = 4 - bin.length() % 4;
	if (offset) {
		for (int i = 0; i < offset; i++)
		{
			bin.insert(0, "0");
		}
	}

	// Chuyen doi moi 4 ky tu nhi phan sang thap luc phan
	string temp;
	int b1, b2, b3, b4;
	int nloop = bin.length() / 4;
	for (int i = 0; i < nloop; i++) {
		b1 = bin[0] - 48;
		b2 = bin[1] - 48;
		b3 = bin[2] - 48;
		b4 = bin[3] - 48;
		temp = Bin_Hex[b1][b2][b3][b4];
		bin = bin.substr(4);
		hex += temp;
	}

	deleteFirstZeroChar(hex);
	return hex;
}

// Ham chuyen chuoi thap luc phan sang nhi phan
string HexToBin(string hex) {

	map<char, string> Hex_Bin;
	Hex_Bin['0'] = "0000";
	Hex_Bin['1'] = "0001";
	Hex_Bin['2'] = "0010";
	Hex_Bin['3'] = "0011";
	Hex_Bin['4'] = "0100";
	Hex_Bin['5'] = "0101";
	Hex_Bin['6'] = "0110";
	Hex_Bin['7'] = "0111";
	Hex_Bin['8'] = "1000";
	Hex_Bin['9'] = "1001";
	Hex_Bin['A'] = "1010";
	Hex_Bin['B'] = "1011";
	Hex_Bin['C'] = "1100";
	Hex_Bin['D'] = "1101";
	Hex_Bin['E'] = "1110";
	Hex_Bin['F'] = "1111";

	map<char, string>::iterator it;
	string bin, temp;

	int len = hex.length();
	for (int i = 0; i < len; i++)
	{
		it = Hex_Bin.find(hex[i]);
		bin += it->second;
	}

	deleteFirstZeroChar(bin);

	return bin;
}

// Ham chuyen chuoi thap phan sang nhi phan
string DecToBin(string dec)
{
	// chuyen doi theo cach thong thuong
	string bin;
	while (dec != "")
	{
		switch (dec[dec.length() - 1] - 48)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 9:
			bin.insert(0, "1");
			break;
		default:
			bin.insert(0, "0");
		}
		DividedBy2(dec);
	}
	return bin;
}

#pragma endregion

//==================== QInt method definition =======================

#pragma region QInt_CONVENIENT_INTERFACE
	// Cap nhap du lieu QInt bang chuoi "data" va co so "base"
void QInt::UpdateByBase(string base, string data)
{
	arrayBits[1] = 0;
	arrayBits[0] = 0;

	QInt one(0, 1);

	// La so am ?
	bool neg = false;
	if (data[0] == '-') {
		data.erase(0, 1);
		neg = true;
	}

	// Chuyen chuoi "data" sang chuoi nhi phan
	string bin;
	if (base == "10") {
		bin = DecToBin(data);
	}
	else if (base == "16") {
		bin = HexToBin(data);
	}
	else {
		bin = data;
	}

	// cap nhap QInt dua tren chuoi nhi phan
	int len = bin.length();
	for (int i = 0; i < len; i++)
	{
		*this << 1;
		if (bin[i] == '1') {
			*this = *this + one;
		}
	}

	if (neg) {
		TwosCompliment();
	}
}

// Ham tinh toan QInt voi operator "oper"
void QInt::CalculateWithOperator(string oper) {
	if (oper == "~") {
		this->operator~();
		return;
	}
	else if (oper == "ror")
	{
		this->ror();
		return;
	}
	else if (oper == "rol")
	{
		this->rol();
		return;
	}
}

// Ham tinh toan QInt voi operator "oper" va doi so QInt x
void QInt::CalculateWithOperator(string oper, const QInt& x) {

	if (oper == "+") {
		*this = this->operator+(x);
		return;
	}
	else if (oper == "-")
	{
		*this = this->operator-(x);
		return;
	}
	else if (oper == "*")
	{
		*this = this->operator*(x);
		return;
	}
	else if (oper == "/")
	{
		*this = this->operator/(x);
		return;
	}
	/*else if (oper == "<")
	{
	*this = this->operator+(x);
	return;
	}
	else if (oper == ">")
	{
	this->ror();
	return;
	}
	else if (oper == "<=")
	{
	this->ror();
	return;
	}
	else if (oper == ">=")
	{
	this->ror();
	return;
	}
	else if (oper == "==")
	{
	this->ror();
	return;
	}
	else if (oper == "!=")
	{
	this->ror();
	return;
	}*/
	else if (oper == "&")
	{
		*this = this->operator&(x);
		return;
	}
	else if (oper == "|")
	{
		*this = this->operator|(x);
		return;
	}
	else if (oper == "^")
	{
		*this = this->operator^(x);
		return;
	}
	else if (oper == "<<")
	{
		this->operator<<(x);
		return;
	}
	else if (oper == ">>")
	{
		this->operator>>(x);
		return;
	}
}

// Ham Chuyen doi QInt thong qua chuoi "base"
string QInt::ConvertToBase(string base) {
	string result;

	// neu am
	if (arrayBits[1] < 0) {
		result = "-";
	}

	if (base == "10") {
		result += ToDec();
	}
	else if (base == "16") {
		result += ToHex();
	}
	else {
		result += ToBin();
	}

	return result;
}

#pragma endregion

#pragma region QInt_Convert_To_Base

// Ham tra ve QInt dang nhi phan
string QInt::ToBin() const
{
	string bin;
	QInt x = *this, one(0, 1);	// copy dulieu QInt sang x

	for (int i = 0; i < 128; i++) { //***
		if (x.arrayBits[0] % 2)
			bin.insert(0, "1");
		else
			bin.insert(0, "0");
		x >> 1;
	}
	deleteFirstZeroChar(bin);
	return bin;
}

// Ham tra ve QInt dang thap luc phan
string QInt::ToHex() const
{
	return BinToHex(ToBin());
}

// Ham tra ve QInt dang thap phan
string QInt::ToDec() const
{
	QInt x = *this; 	// copy dulieu QInt sang x, 
	string result;
	if (arrayBits[1] < 0) {
		result += '-';
		x.TwosCompliment();
	}
	result += BinToDec(x.ToBin());
	return result;
}

#pragma endregion

//=== QInt operator ===
#pragma region QINT_CALCULATE_OPERATORS

	// Ham bu2 cho QInt
void QInt::TwosCompliment()
{
	QInt one(0, 1);
	this->operator~();
	*this = *this + one;
}

QInt QInt::operator+ (const QInt& x)const {
	QInt a = *this, b = x, temp;
	QInt zero;

	while (1)
	{
		temp = a;
		a = a ^ b;
		b = temp & b;
		if (b == zero) {
			return a;
		}
		b << 1;
	}
}

QInt QInt::operator- (const QInt& x)const {
	QInt b = x;
	b.TwosCompliment();
	return *this + b;
}

QInt QInt::operator* (const QInt& x)const {
	QInt a = *this, b = x, c;		// copy QInt -> a		x -> b		c = a*b (result)

	for (int i = 0; i < 128; i++)
	{
		c << 1;
		if (b.arrayBits[1] < 0) {	// <0 thi bit dau tien la 1
			c = c + a;
		}
		b << 1;
	}
	return c;
}

// Ham chia lay nguyen cua 2 so QInt duong
QInt devidePositiveQInt(const QInt& x, const QInt& y) {
	QInt quotient(0, 1);
	QInt b = y;

	if (b == x) {
		return QInt(0, 1);
	}
	else if (x < b) {
		return QInt(0, 0);
	}

	do {
		b << 1;
		quotient << 1;
	} while (b <= x);
	b >> 1;
	quotient >> 1;

	// 1 chut de quy
	quotient = quotient + ((x - b) / y);

	return quotient;
}

QInt QInt::operator/(const QInt& x)const {
	QInt a = *this;
	QInt b = x;
	QInt c;

	bool neg = false;
	if (a.arrayBits[1] < 0) {
		neg = !neg;
		a.TwosCompliment();
	}
	if (x.arrayBits[1] < 0) {
		neg = !neg;
		b.TwosCompliment();
	}

	// chia c = a / b duong
	c = devidePositiveQInt(a, b);


	if (neg) {
		c.TwosCompliment();
	}
	return c;
}

#pragma endregion

#pragma region QInt_COMPARE_OPERATORS

bool QInt::operator< (const QInt& b) const {
	if (arrayBits[1] < b.arrayBits[1]) { return true; }
	else
	{
		if (arrayBits[1] == b.arrayBits[1]) {
			if (*((unsigned long long*) & arrayBits[0]) < *((unsigned long long*) & b.arrayBits[0])) { return true; }
		}
	}
	return false;
}

bool QInt::operator> (const QInt& b)const {
	if (arrayBits[1] > b.arrayBits[1]) { return true; }
	else
	{
		if (arrayBits[1] == b.arrayBits[1]) {
			if (*((unsigned long long*) & arrayBits[0]) > * ((unsigned long long*) & b.arrayBits[0])) { return true; }
		}
	}
	return false;
}

bool QInt::operator== (const QInt& b) const {
	if (arrayBits[1] != b.arrayBits[1]) { return false; }
	if (arrayBits[0] != b.arrayBits[0]) { return false; }
	return true;
}

bool QInt::operator!= (const QInt& b)const {
	return !(*this == b);
}

bool QInt::operator<= (const QInt& b) const {
	return !(*this > b);
}

bool QInt::operator>= (const QInt& b)const {
	return !(*this < b);
}

#pragma endregion

#pragma region QInt_BITWISE_OPERATORS

QInt QInt::operator& (const QInt& b) {
	QInt c;

	c.arrayBits[0] = arrayBits[0] & b.arrayBits[0];
	c.arrayBits[1] = arrayBits[1] & b.arrayBits[1];

	return c;
}

QInt QInt::operator| (const QInt& b) {
	QInt c;

	c.arrayBits[0] = arrayBits[0] | b.arrayBits[0];
	c.arrayBits[1] = arrayBits[1] | b.arrayBits[1];

	return c;
}

QInt QInt::operator^ (const QInt& b) {
	QInt c;

	c.arrayBits[0] = arrayBits[0] ^ b.arrayBits[0];
	c.arrayBits[1] = arrayBits[1] ^ b.arrayBits[1];

	return c;
}

void QInt::operator~() {
	arrayBits[0] = ~arrayBits[0];
	arrayBits[1] = ~arrayBits[1];
}

void QInt::operator<<(unsigned int n) {
	n = n % 128;
	if (n > 64) {
		arrayBits[1] = arrayBits[0] << (n - 64);
		arrayBits[0] = 0;
	}
	else
	{
		unsigned long long* p = (unsigned long long*) arrayBits;
		p[1] = (p[1] << n) | (p[0] >> (64 - n));
		arrayBits[0] = arrayBits[0] << n;
	}
}

void QInt::operator>>(unsigned int n) {
	n = n % 128;
	if (n > 64) {
		arrayBits[0] = arrayBits[1] >> (n - 64);
		arrayBits[1] = arrayBits[1] >> 63;
	}
	else
	{
		unsigned long long* p = (unsigned long long*) arrayBits;
		p[0] = (p[0] >> n) | (p[1] << (64 - n));
		arrayBits[1] = arrayBits[1] >> n;
	}
}

void QInt::operator<<(const QInt& b)
{
	string s = b.ToDec();
	unsigned int n = (unsigned int)stoi(s);
	*this << n;
}

void QInt::operator>>(const QInt& b)
{
	string s = b.ToDec();
	unsigned int n = (unsigned int)stoi(s);
	*this >> n;
}

void QInt::ror(unsigned int n) {
	unsigned long long* p = (unsigned long long*) arrayBits;
	unsigned long long temp = p[0] << (sizeof(long long) * 8 - n);
	p[0] = (p[0] >> n) | (p[1] << (sizeof(long long) * 8 - n));
	p[1] = p[1] >> n | temp;
}

void QInt::rol(unsigned int n) {
	unsigned long long* p = (unsigned long long*) arrayBits;
	unsigned long long temp = p[1] >> (sizeof(long long) * 8 - n);
	p[1] = (p[1] << n) | (p[0] >> (sizeof(long long) * 8 - n));
	p[0] = p[0] << n | temp;
}

#pragma endregion
