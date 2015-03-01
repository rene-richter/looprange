#include <iostream>
#include "loop.h"

int main()
{
	for (auto i : loop::range(5)) std::cout << i << ' ';
	std::cout << '\n';
	// 0 1 2 3 4

	for (auto i : loop::range_down(5)) std::cout << i << ' ';
	std::cout << '\n';
	// 4 3 2 1 0

	for (auto i : loop::range(5, 10)) std::cout << i << ' ';
	std::cout << '\n';
	// 5 6 7 8 9
	
	for (auto i : loop::range(0, 10, 2)) std::cout << i << ' ';
	std::cout << '\n';
	// 0 2 4 6 8

	for (auto i : loop::range(0, 10, 2, true)) std::cout << i << ' ';
	std::cout << '\n';
	// 0 2 4 6 8 10
	
	for (auto i : loop::range(10, 0, -2)) std::cout << i << ' ';
	std::cout << '\n';
	// 10 8 6 4 2

	for (auto i : loop::range(10, 0, -2, true)) std::cout << i << ' ';
	std::cout << '\n';
	// 10 8 6 4 2 0
	
	std::cout << "-----------------\n";

	// ---[ non-integral range ]---
	
	for (auto x : loop::linrange(0., 2., 4)) std::cout << x << ' ';
	std::cout << '\n';
	// 0 .5 1 1.5 2
	
	for (auto x : loop::linrange(0., 2., 4, loop::interval::closed)) std::cout << x << ' ';
	std::cout << '\n';
	// 0 .5 1 1.5 2

	for (auto x : loop::linrange(0., 2., 4, loop::interval::rightopen)) std::cout << x << ' ';
	std::cout << '\n';
	// 0 .5 1 1.5

	for (auto x : loop::linrange(0., 2., 4, loop::interval::leftopen)) std::cout << x << ' ';
	std::cout << '\n';
	// .5 1 1.5 2

	for (auto x : loop::linrange(0., 2., 4, loop::interval::open)) std::cout << x << ' ';
	std::cout << '\n';
	// .5 1 1.5

	for (auto x : loop::linrange(0., 1., 3)) std::cout << x << ' ';
	std::cout << '\n';
	// 0 0.333333 0.666667 1

}
