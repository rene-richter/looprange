#include <iostream>
#include "../loop.h"
#include "benchmark.h"

bool demo(int steps)
{
	double a = 1, b = 6;
	int n = steps-1; // number of intervals
	
	double sum1 = 0;
	for (auto i = 0; i <= n; ++i)
	{
		auto x = ((n-i)*a + i*b)/n;
		sum1 += x;
	}

	double a_n = a/n, b_n = b/n;
	double sum2 = 0;
	for (auto i = 0; i <= n; ++i)
	{
		auto x = (n-i)*a_n + i*b_n;
		sum2 += x;
	}

	auto dx = (b - a)/n; // dx > 0
	double sum3 = 0;
	
	for (auto x = a; x < b + dx/2; x += dx)
	{
		sum3 += x;
	}

	std::cout 
		<< steps << ' '
		<< sum1 << ' ' << sum2 << ' ' << sum3 << ' '
		<< (sum1 == sum2? "==" : "<>") << ' '	
		<< (sum1 == sum3? "==" : "<>") << ' '	
		<< (sum2 == sum3? "==" : "<>") << '\n';	
	
	return true;
}

void benchmark()
{	
	double a = 1, b = 6;
	double sum1, sum2, sum3, sum4, sum5;
	
	auto x_plus_dx = [&](int n) 
		{  
			auto dx = (b - a)/n; // dx > 0
			auto end = b + dx/2;
			double sum = 0;
			for (auto x = a; x < end; x += dx)
			{
				sum += x;
			}
			sum1 = sum;
		};

	auto i_times_dx = [&](int n) 
		{  
			double sum = 0;
			auto dx = (b - a)/n;
			for (auto i = 0; i <= n; ++i)
			{
				auto x = a + i*dx;
				sum += x;
			}

			sum2 = sum;
		};	
	
	auto with_div = [&](int n) 
		{  
			double sum = 0;
			for (auto i = 0; i <= n; ++i)
			{
				auto x = ((n-i)*a + i*b)/n;
				sum += x;
			}
			sum3 = sum;
		};
		
	auto without_div = [&](int n) 
		{  
			double a_n = a/n, b_n = b/n;
			double sum = 0;
			for (auto i = 0; i <= n; ++i)
			{
				auto x = (n-i)*a_n + i*b_n;
				sum += x;
			}
			sum4 = sum;
		};
		
	auto linspace = [&](int n) 
		{  
			double sum = 0;
			for (auto x : loop::linspace(a, b, n))
			{
				sum += x;
			}
			sum5 = sum;
		};	
	
    bmk::benchmark<std::chrono::nanoseconds> bm;

    bm.run("x+=dx",      10, x_plus_dx,   "steps", { 10, 100, 1000, 10000, 100000 }); 
    bm.run("x=a+i*dx",   10, i_times_dx,  "steps", { 10, 100, 1000, 10000, 100000 }); 
    bm.run("interpol /", 10, with_div,    "steps", { 10, 100, 1000, 10000, 100000 }); 
    bm.run("interpol *", 10, without_div, "steps", { 10, 100, 1000, 10000, 100000 }); 
    bm.run("linspace",   10, linspace,    "steps", { 10, 100, 1000, 10000, 100000 }); 

    bm.serialize("double type for loops", "benchmark_results.txt");
	
	std::cout 
		<< sum1 << ' ' 
		<< sum2 << ' ' 
		<< sum3 << ' ' 
		<< sum4 << ' ' 
		<< sum5 << '\n';
}

int main()
{
	benchmark();
	/*
	for (int i = 2; i <= 50; ++i)
	{
		demo(i);
	}
	*/
}

