#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <set>
#include "QInt.h"
using namespace std;

// ===== Parse file function =====

	// Ham phan tich input
int ParseLine(vector<string> v);

	// Ham getlint => vector
vector<string> GetSVector(string s);

//=================================



//==== MY MAIN FUNC ====
int main(int argc, char* argv[])
{
	ifstream in;
	ofstream out;

	in.open(argv[1]);
	out.open(argv[2]);

		// Neu mo file that bai
	if (in.fail() || out.fail()) { 
		cout << "Cant find file"; 
		return -1;
	}

	int kind;				// loai phep tinh
	string result;			// output string
	string stringLine;		// Line by string
	vector<string> vLine;	// Line by vector
	while (getline(in, stringLine))			
	{
		result = "";
		vLine = GetSVector(stringLine);		// chuoi to vector
		kind = ParseLine(vLine);			// phan tich chuoi
		switch (kind)
		{
		case 0:		// chuyen he co so
		{
			QInt q;
			q.UpdateByBase(vLine[0], vLine[2]);
			result = q.ConvertToBase(vLine[1]);
			break;
		}
		case 1:		// phep tinh 1 tham so
		{
			QInt q;
			q.UpdateByBase(vLine[0], vLine[2]);
			q.CalculateWithOperator(vLine[1]);
			result = q.ConvertToBase(vLine[0]);
			break;
		}
		case 2:		// phep tinh 2 tham so
		{
			  QInt q, q2;
			  q.UpdateByBase(vLine[0], vLine[1]);
			  q2.UpdateByBase(vLine[0], vLine[3]);
			  q.CalculateWithOperator(vLine[2],q2);
			  result = q.ConvertToBase(vLine[0]);
		}
			break;
		case 3:		// phep tinh dich bit
		{
			QInt q, q2;
			q.UpdateByBase(vLine[0], vLine[1]);
			q2.UpdateByBase("10", vLine[3]);
			q.CalculateWithOperator(vLine[2], q2);
			result = q.ConvertToBase(vLine[0]);
		}
		break;
		default:
			break;
		}
		result += '\n';
		out << result;
	}
	in.close();
	out.close();
	
	return 0;
}



// ==== Parse file function defination ===
	
	// Ham phan tich input
vector<string> GetSVector(string s) {
	vector<string> v;
	istringstream ss(s);
	do
	{
		string temp;
		ss >> temp;		// tach chuoi
		v.push_back(temp);
	} while (ss);
	return v;
}

	// Ham getlint => vector
int ParseLine(vector<string> v) {
	
	set<string> shiftOperator;
	shiftOperator.insert("<<");
	shiftOperator.insert(">>");

	set<string> operator2Par;
	operator2Par.insert("+"); 
	operator2Par.insert("-");
	operator2Par.insert("*");
	operator2Par.insert("/");
	operator2Par.insert("<");
	operator2Par.insert(">");
	operator2Par.insert("<=");
	operator2Par.insert(">=");
	operator2Par.insert("==");
	operator2Par.insert("!=");
	operator2Par.insert("&");
	operator2Par.insert("|");
	operator2Par.insert("^");

	set<string> operator1Par;
	operator1Par.insert("~");
	operator1Par.insert("rol");
	operator1Par.insert("ror");

	for (int i = 1; i < v.size(); i++)
	{
		if (shiftOperator.find(v[i]) != shiftOperator.end()) {
			return 3;
		}
	}

	for (int i = 1; i < v.size(); i++)
	{
		if (operator2Par.find(v[i]) != operator2Par.end()) {
			return 2;
		}
	}

	for (int i = 1; i < v.size(); i++)
	{
		if (operator1Par.find(v[i]) != operator1Par.end()) {
			return 1;
		}
	}

	return 0;
}