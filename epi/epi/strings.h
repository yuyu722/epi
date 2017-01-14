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

//////////////////////////////////////////////////////////////////////////////////////
//								Replace and remove									//
//////////////////////////////////////////////////////////////////////////////////////
int ReplaceAndRemove(int size, char s[])
{
	// acdbbca
	int write_index = 0;
	int a_count = 0;
	for (int i = 0; i < size; ++i)
	{
		if (s[i] != 'b')
			s[write_index++] = s[i];
		if (s[i] == 'a')
			++a_count;
	}
	
	int curr_index = write_index - 1;
	write_index = curr_index + a_count;
	int final_size = write_index + 1;
	while (curr_index >= 0)
	{
		if (s[curr_index] == 'a')
		{
			s[write_index--] = 'd';
			s[write_index--] = 'd';
		}
		else
		{
			s[write_index--] = s[curr_index];
		}
		--curr_index;
	}

	return final_size;
}

//////////////////////////////////////////////////////////////////////////////////////
//								Test Palindromicity									//
//////////////////////////////////////////////////////////////////////////////////////
bool IsPalindrom(const string& s)
{
	/*
	int l = 0;
	int u = s.size() - 1;
	while (l <= u && s[l] == s[u])
	{
		++l;
		--u;
	}
	return l >= u;
	*/
	int i = 0, j = s.size() - 1;
	while (i < j)
	{
		while (!isalnum(s[i]) && i < j)
			++i;
		while (!isalnum(s[j]) && i < j)
			--j;
		if (tolower(s[i]) != tolower(s[j]))
			return false;

		++i;
		--j;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
//						Reverse All the words in a sentence							//
//////////////////////////////////////////////////////////////////////////////////////
void ReverseWords(string* s)
{
	reverse(s->begin(), s->end());
	
	int start = 0, end;
	while ((end = s->find(" ", start)) != string::npos)
	{
		reverse(s->begin() + start, s->begin() + end);
		start = end + 1;
	}

	reverse(s->begin() + start, s->end());
}

//////////////////////////////////////////////////////////////////////////////////////
//					Compute all mnemonics for a phone number						//
//////////////////////////////////////////////////////////////////////////////////////
const int kNumTelDigits = 10;

const array<string, kNumTelDigits> kMapping = {
	{"0", "1", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"}
};

void PhoneMnemonicHelper(const string& phone_number, int digit, string* partial_mnemonic, vector<string>* mnemonics)
{
	if (digit == phone_number.size())
	{
		mnemonics->emplace_back(*partial_mnemonic);
	}
	else
	{
		for (char c : kMapping[phone_number[digit] - '0'])
		{
			(*partial_mnemonic)[digit] = c;
			PhoneMnemonicHelper(phone_number, digit + 1, partial_mnemonic, mnemonics);
		}
	}
}

vector<string> PhoneMnemonic(const string& phone_number)
{
	string partial_mnemonic(phone_number.size(), 0);
 	vector<string> mnemonics;
	PhoneMnemonicHelper(phone_number, 0, &partial_mnemonic, &mnemonics);
	return mnemonics;
}

//////////////////////////////////////////////////////////////////////////////////////
//								The Look-And-See Problem							//
//////////////////////////////////////////////////////////////////////////////////////
string NextNumber(const string& s)
{
	string ret;
	for (int i = 0; i < s.size(); ++i)
	{
		int count = 1;
		while (i + 1 < s.size() && s[i] == s[i + 1])
		{
			++i, ++count;
		}
		ret += to_string(count) + s[i];
	}
	return ret;
}

string LookAndSay(int n)
{
	string s = "1";
	for (int i = 1; i < n; ++i)
	{
		s = NextNumber(s);
	}
	return s;
}

//////////////////////////////////////////////////////////////////////////////////////
//							Convert from Roman to decimal							//
//////////////////////////////////////////////////////////////////////////////////////
int RomanToDecimal(const string& s)
{	
	unordered_map<char, int> T = {
		{ 'I', 1 },
		{ 'V', 5 },
		{ 'X', 10 },
		{ 'L', 50 },
		{ 'C', 100 },
		{ 'D', 500 },
		{ 'M', 1000 }
	};

	int sum = T[s.back()];
	for (int i = s.length() - 2; i >= 0; --i)
	{
		if (T[s[i]] < T[s[i + 1]])
		{
			sum -= T[s[i]];
		}
		else
		{
			sum -= T[s[i]];
		}
	}

	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////
//							Compute all valid IP address							//
//////////////////////////////////////////////////////////////////////////////////////
bool IsValidPart(const string& s)
{
	if (s.size() > 3)
		return false;

	// "00", "000", "01", etc
	if (s.front() == '0' && s.size() > 1)
		return false;

	int val = stoi(s);
	return val <= 255 && val >= 0;
}

vector<string> GetValidIPAddress(const string& s)
{
	vector<string> result;
	for (size_t i = 1; i < 4 && i < s.size(); ++i)
	{
		auto first = s.substr(0, i);
		if (IsValidPart(first))
		{
			for (size_t j = 1; i + j < s.size() && j < 4; ++j)
			{
				auto second = s.substr(i, j);
				if (IsValidPart(second))
				{
					for (size_t k = 1; i + j + k < s.size() && k < 4; ++k)
					{
						auto third = s.substr(i + j, k), fourth = s.substr(i + j + k);
						if (IsValidPart(third) && IsValidPart(fourth))
						{
							result.emplace_back(first + "." + second + "." + third + "." + fourth);
						}
					}
				}
			}
		}
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//								Write a string sinusoidally							//
//////////////////////////////////////////////////////////////////////////////////////
string SnakeString(const string& s)
{
	string result;

	for (size_t i = 1; i < s.size(); i += 4)
	{
		result += s[i];
	}

	for (size_t i = 0; i < s.size(); i += 2)
	{
		result += s[i];
	}

	for (size_t i = 3; i < s.size(); i += 4)
	{
		result += s[i];
	}

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//							Implement Run-Length Encoding							//
//////////////////////////////////////////////////////////////////////////////////////
string Decoding(const string& s)
{
	int count = 0;
	string result;
	for (char c : s)
	{
		if (isdigit(c))
		{
			count = count * 10 + c - '0';
		}
		else
		{
			result.append(count, c);
			count = 0;
		}
	}

	return result;
}

string Encoding(const string& s)
{
	string result;

	for (int i = 1, count = 1; i <= s.size(); ++i)
	{
		if (i == s.size() || s[i] != s[i - 1])
		{
			result += to_string(count) + s[i - 1];
			count = 1;
		}
		else
		{
			++count;
		}
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//					Find the first occurrence of a substring						//
//////////////////////////////////////////////////////////////////////////////////////
const int kBase = 26, kMod = 997;

int RabinKarp(const string& t, const string& s)
{
	if (s.size() > t.size())
	{
		return -1;
	}

	int t_hash = 0, s_hash = 0;
	int power_s = 1;
	for (int i = 0; i < s.size(); ++i)
	{
		power_s = i ? power_s * kBase % kMod : 1;
		t_hash = (t_hash * kBase + t[i]) % kMod;
		s_hash = (s_hash * kBase + s[i]) % kMod;
	}

	for (int i = s.size(); i < t.size(); ++i)
	{
		// Checks the two substrings are actually equal or not, to protect against hash collision.
		if (t_hash == s_hash && !t.compare(i - s.size(), s.size(), s))
			return i - s.size();

		// Use rolling hash to compute the new hash code.
		t_hash -= (t[i - s.size()] * power_s) % kMod;
		if (t_hash < 0)
			t_hash += kMod;
		t_hash = (t_hash * kBase + t[i]) % kMod;

		// Tries to match s and t[t.size() - s.size() : t.size() - 1].
		if (t_hash == s_hash && t.compare(t.size() - s.size(), s.size(), s) == 0)
			return t.size() - s.size();
	}
	return -1; // s is not a substring of t.
}