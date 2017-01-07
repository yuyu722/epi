#pragma once
#include "stdfx.h"

//////////////////////////////////////////////////////////////////////////////////////
//										Parity										//
//////////////////////////////////////////////////////////////////////////////////////
/* The parity of a binary word is 1 if ther number of 1s in the word is odd, 
 * otherwise, it is 0.
 * For example: the parity of 1011 is 1, and the parity of 10001000 is 0.
 */

// 1. Brute-force: O(n)
short Parity1(unsigned long x)
{
	short result = 0;
	while (x)
	{
		result += (x & 1);
		x >>= 1;
	}
	return result % 2;
}

// 2. Best and Average - Improved 1
short Parity2(unsigned long x)
{
	short result = 0;
	while (x)
	{
		result ^= 1;
		x &= (x - 1); // Drops the lowest set bit of x.
	}
	return result;
}
// Note: Let k be the number of bits set to 1, then time complexisty of 
// the algorithm is O(k), the worst case is still O(n) 

// 3. Use lookup table : O(n/L)
array<short, 1 << 16> BuildTable()
{
	array<short, 1 << 16> result;
	for (int i = 0; i < (1 << 16); ++i)
	{
		result[i] = Parity1(i);
	}
	return result;
}

static array<short, 1 << 16> precomputed_parity = BuildTable();

short Parity3(unsigned long x)
{
	const int kWordSize = 16;
	const int kBitMask = 0xFFFF;
	return precomputed_parity[x >> (3 * kWordSize)] ^
		precomputed_parity[x >> (2 * kWordSize) & kBitMask] ^
		precomputed_parity[x >> kWordSize & kBitMask] ^
		precomputed_parity[x & kBitMask];
}

// 4. Use XOR: O(log(n))
short Parity4(unsigned long x)
{
	x ^= x >> 32;
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 0x1;
}

//////////////////////////////////////////////////////////////////////////////////////
//										Swap Bits									//
//////////////////////////////////////////////////////////////////////////////////////
long SwapBit(long x, int i, int j)
{
	if (((x >> i) & 1) != ((x >> j) & 1))
	{
		unsigned long bitMask = (1L << i) | (1L << j);
		x ^= bitMask;
	}
	return x;
}

//////////////////////////////////////////////////////////////////////////////////////
//					Find A Closest Integer With The Same Weight						//
//////////////////////////////////////////////////////////////////////////////////////
const int kNumUnsignBits = 64;

unsigned long ClosetIntSameBitCount(unsigned long x)
{
	for (int i = 0; i < kNumUnsignBits - 1; ++i)
	{
		if (((x >> i) & 1) != ((x >> (i + 1)) & 1))
		{
			x ^= (1UL << i) | (1UL << (i + 1));
			return x;
		}
	}
	throw invalid_argument("All bits are 0 or 1");
}

//////////////////////////////////////////////////////////////////////////////////////
//					Compute X x Y Without Arithmetical Operators					//
//////////////////////////////////////////////////////////////////////////////////////
unsigned Add(unsigned a, unsigned b)
{
	unsigned sum = 0, carryin = 0, k = 1, temp_a = a, temp_b = b;
	while (temp_a || temp_b)
	{
		unsigned ak = a & k, bk = b & k;
		unsigned carryout = (ak & bk) | (ak & carryin) | (bk & carryin);
		sum |= (ak ^ bk ^ carryin);
		carryin = carryout << 1, k <<= 1, temp_a >>= 1, temp_b >>= 1;
	}
	return sum | carryin;
}

unsigned Multiply(unsigned x, unsigned y)
{
	unsigned sum = 0;
	while (x)
	{
		if (x & 1)
		{
			sum = Add(sum, y);
		}
		x >>= 1, y <<= 1;
	}
	return sum;
}

//////////////////////////////////////////////////////////////////////////////////////
//									Compute X / Y									//
//////////////////////////////////////////////////////////////////////////////////////
unsigned Divide(unsigned x, unsigned y)
{
	unsigned result = 0;
	int power = 32;
	unsigned long long y_power = static_cast<unsigned long long>(y) << power;
	while (x >= y)
	{
		while (y_power > x)
		{
			y_power >>= 1;
			--power;
		}

		result += 1U << power;
		x -= y_power;
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//									Compute X Pow(Y)								//
//////////////////////////////////////////////////////////////////////////////////////
unsigned Power(double x, int y)
{
	double result = 1.0;
	long long power = y;
	if (y < 0)
	{
		power = -power;
		x = 1.0 / x;
	}

	while (power)
	{
		if (power & 1)
		{
			result *= x;
		}
		x *= x, power >>= 1;
	}
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//									Reverse Digits									//
//////////////////////////////////////////////////////////////////////////////////////
long Reverse(int x)
{
	bool is_negative = x < 0;
	long result = 0, x_remaining = abs(x);
	while (x_remaining)
	{
		int mod = x_remaining % 10;
		result = result * 10 + x_remaining % 10;
		x_remaining /= 10;
	}
	return is_negative ? -result : result;
}

//////////////////////////////////////////////////////////////////////////////////////
//					Check if a decimal integer is a palindrome						//
//////////////////////////////////////////////////////////////////////////////////////
bool IsPalindromeNumber(int x)
{
	if (x < 0) return false;
	else if (x == 0) return true;

	const int num_digits = static_cast<int>(floor(log10(x) + 1));
	int msd_mask = static_cast<int>(pow(10, num_digits - 1));
	for (int i = 0; i < num_digits / 2; ++i)
	{
		if (x / msd_mask != x % 10)
			return false;
		x %= msd_mask;
		x /= 10;
		msd_mask /= 100;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////
//							Generate uniform random numbers							//
//////////////////////////////////////////////////////////////////////////////////////
int ZeroOneRandom()
{
	std::random_device rd;
	default_random_engine gen(rd());
	uniform_int_distribution<int> dis(0, 1);
	return dis(gen);
}

int UniformRandom(int lower_bound, int upper_bound)
{
	int number_of_outcomes = upper_bound - lower_bound + 1, result;
	do
	{
		result = 0;
		for (int i = 0; (1 << i) < number_of_outcomes; ++i)
		{
			result = (result << 1) | ZeroOneRandom();
		}
	} while (result >= number_of_outcomes);
	return result + lower_bound;
}