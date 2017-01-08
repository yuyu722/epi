#pragma once
#include "stdfx.h"

//////////////////////////////////////////////////////////////////////////////////////
//						Interconvert strings and integers							//
//////////////////////////////////////////////////////////////////////////////////////
string IntToString(int x)
{
	bool is_negative = false;
	if (x < 0)
	{
		x = -x;
		is_negative = true;
	}

	string s;
	do
	{
		s += '0' + x % 10;
		x /= 10;
	} while (x);

	if (is_negative)
		s += "-";

	reverse(s.begin(), s.end());
	
	return s;
}

int StringToInt(const string& s)
{
	bool is_negative = s[0] == '-';
	int result = 0;
	for (int i = is_negative ? 1 : 0; i < s.size(); ++i)
	{
		int digit = s[i] - '0';
		result = result * 10 + digit;
	}

	return is_negative ? -result : result;
}

//////////////////////////////////////////////////////////////////////////////////////
//						Interconvert strings and integers							//
//////////////////////////////////////////////////////////////////////////////////////
string ConvertBase(const string& s, int b1, int b2)
{
	bool is_negative = s.front() == '-';
	int decimal = 0;
	for (size_t i = is_negative ? 1 : 0; i < s.size(); ++i)
	{
		decimal *= b1;
		decimal += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
	}

	string result = "";
	do
	{
		int rem = decimal % b2;
		char c = rem >= 10 ? ('A' + (10 - rem)) : ('0' + rem);
		result.push_back(c);
		decimal /= b2;
	} while (decimal);

	if (is_negative)
		result.push_back('-');

	reverse(result.begin(), result.end());
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//					Compute the spreadsheet column encoding							//
//////////////////////////////////////////////////////////////////////////////////////
int SSDecodeColID(const string& col)
{
	int ret = 0;
	for (char c : col)
	{
		ret = ret * 26 + c - 'A' + 1;
	}
	return ret;
}