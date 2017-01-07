#pragma once
#include "stdfx.h"

//////////////////////////////////////////////////////////////////////////////////////
//								Dutch Flag Partition								//
//////////////////////////////////////////////////////////////////////////////////////
typedef enum { RED, WHITE, BLUE} Color;

template<typename T>
void swap(vector<T>& v, int i, int j)
{
	T temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr)
{
	vector<Color>& A = *A_ptr;
	Color pivot = A[pivot_index];

	int smaller = 0;
	for (int i = 0; i < A.size(); ++i)
	{
		if (A[i] < pivot)
			swap<Color>(A, i, smaller++);
	}

	int larger = A.size() - 1;
	for (int i = A.size() - 1; i >= 0 && A[i] >= pivot; --i)
	{
		if (A[i] > pivot)
			swap<Color>(A, i, larger--);
	}
}

void DutchFlagPartition_2(int pivot_index, vector<Color>* A_ptr)
{
	vector<Color>& A = *A_ptr;
	Color pivot = A[pivot_index];

	int smaller = 0, equal = 0, larger = A.size();
	while (equal < larger)
	{
		if (A[equal] < pivot)
			swap(A, smaller++, equal++);
		else if (A[equal] == pivot)
			++equal;
		else
			swap(A, equal, --larger);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//						Increment An Arbitary-Precision integer						//
//////////////////////////////////////////////////////////////////////////////////////
vector<int> PlusOne(vector<int> A)
{
	++A.back();
	for (int i = A.size() - 1; i > 0 && A[i] == 10; --i)
	{
		A[i] = 0;
		++A[i - 1];
	}

	if (A[0] == 10)
	{
		A[0] = 0;
		A.insert(A.begin(), 1);
	}

	return A;
}

//////////////////////////////////////////////////////////////////////////////////////
//						Multiply Two Arbitrary-Precision Integers					//
//////////////////////////////////////////////////////////////////////////////////////
vector<int> Multiply(vector<int> num1, vector<int> num2)
{
	bool is_negative = (num1.front() < 0 && num2.front() > 0) || (num1.front() > 0 && num2.front() < 0);
	num1.front() = abs(num1.front());
	num2.front() = abs(num2.front());

	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());

	vector<int> result(num1.size() + num2.size(), 0);
	for (int i = 0; i < num1.size(); ++i)
	{
		for (int j = 0; j < num2.size(); ++j)
		{
			result[i + j] += num1[i] * num2[j];
			result[i + j + 1] += result[i + j] / 10;
			result[i + j] %= 10;
		}
	}

	while (result.size() > 0 && result.back() == 0)
		result.pop_back();

	reverse(result.begin(), result.end());
	if (is_negative)
		result.front() *= -1;

	return result;
}

//////////////////////////////////////////////////////////////////////////////////////
//								Advancing Through An Array							//
//////////////////////////////////////////////////////////////////////////////////////
bool CanReachEnd(const vector<int>& max_advance_steps)
{
	int furthest_reach_so_far = 0;
	int last_index = max_advance_steps.size() - 1;
	for (int i = 0; i <= furthest_reach_so_far && furthest_reach_so_far < last_index; ++i)
		furthest_reach_so_far = max(furthest_reach_so_far, max_advance_steps[i] + i);

	return furthest_reach_so_far >= last_index;
}

//////////////////////////////////////////////////////////////////////////////////////
//						Delete Duplicates from a sorted array						//
//////////////////////////////////////////////////////////////////////////////////////
size_t DeleteDuplicates(vector<int>* A_ptr)
{
	vector<int> &A = *A_ptr;
	if (A.empty())
		return 0;
	int write_index = 1;
	for (int i = 1; i < A.size(); ++i)
	{
		if (A[write_index - 1] != A[i])
			A[write_index++] = A[i];
	}
	return write_index;
}

//////////////////////////////////////////////////////////////////////////////////////
//								Buy and sell a stock once							//
//////////////////////////////////////////////////////////////////////////////////////
double BuyAndSellStockOnce(const vector<double>& prices)
{
	double min_price_so_far = numeric_limits<double>::max(), max_profit = 0;
	for (const double& price : prices)
	{
		double max_profit_sell_today = price - min_price_so_far;
		max_profit = max(max_profit, max_profit_sell_today);
		min_price_so_far = min(min_price_so_far, price);
	}
	return max_profit;
}