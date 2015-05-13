#include <ctime>
#include <iostream>
#include <vector>
#include "../loop.h"

void timing(int n)
{
	std::vector<int> v(n, 1);

	int sum1 = 0, sum2 = 0, sum3 = 0;
	
	auto start1 = std::clock();

	for (int j = 0; j < 1000; ++j)
	{
		for (int i = 0; i < n; ++i) sum1 += v[i];
	}
	
	auto end1 = std::clock();
	auto start2 = end1;
	
	for (int j = 0; j < 1000; ++j)
	{
		for (auto x : v) sum2 += x;
	}
	
	auto end2 = std::clock();
	auto start3 = end2;
	
	for (int j = 0; j < 1000; ++j)
	{
		for (auto i : loop::range(n)) sum3 += v[i];
	}
	
	auto end3 = std::clock();

	auto time1 = (end1 - start1)/double(CLOCKS_PER_SEC);
	auto time2 = (end2 - start2)/double(CLOCKS_PER_SEC);
	auto time3 = (end3 - start3)/double(CLOCKS_PER_SEC);
	
	std::cout << n << '\t' << time1 << '\t' << time2 << '\t' << time3 
		<< (sum1 == sum2 && sum2 == sum3 ? " ==" : " !=" ) << '\n';
}

int main()
{
	for (int i = 1; i < 10000000; i *= 2) timing(i);
}