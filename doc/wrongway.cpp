// How to interpolate real numbers the wrong way - R.Richter 2015-03-01

#include <iostream>

bool demo(int steps)
{
	double a = 1, b = 6;
	int n = steps-1; // number of intervals
	
	// std::cout.precision(20);
	// right way:
	for (auto i = 0; i <= n; ++i)
	{
		auto x = ((n-i)*a + i*b)/n;
//		std::cout << x << ' ';
	}
//	std::cout << '\n';
	
	auto dx = (b - a)/n;
	int count = 0;
	
	// wrong way: (rounding errors add up)
	for (auto x = a; x <= b; x += dx)
	{
		++count;
//		std::cout << x << ' ';
	}
//	std::cout << '\n';
//	std::cout << "steps: " << steps << " count: " <<  count << '\n'; 
//		<< "\n------------\n";

	std::cout << steps << '\t' 
		<< (count == steps ? "==" : (count < steps ? "<" : ">")) << '\n';
	
	return count != steps;
}

int main()
{
	int diffs = 0;
	int count = 0;

	for (int i = 2; i <= 50; ++i)
	{
		++count;
		diffs += demo(i);
	}
	std::cout << diffs << " of " << count << " diffs\n";
}
