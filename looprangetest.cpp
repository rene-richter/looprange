#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "loop.h"

TEST_CASE("integer range, valid parameter values", "[intrange]" ) 
{
	std::vector<int> v;
	REQUIRE(v.size() == 0u);

	SECTION("range(0)") 
	{
		for (auto i : loop::range(0)) v.push_back(i);
		REQUIRE(v.size() == 0u);
	}

	SECTION("range(5)") 
	{
		for (auto i : loop::range(5)) v.push_back(i);
		REQUIRE(v.size() == 5u);
		REQUIRE(v == std::vector<int>({ 0, 1, 2, 3, 4 }));
	}

	SECTION("range_down(5)") 
	{
		for (auto i : loop::range_down(5)) v.push_back(i);
		REQUIRE(v.size() == 5u);
		REQUIRE(v == std::vector<int>({ 4, 3, 2, 1, 0 }));
	}

	SECTION("range(0, 1, 2)") 
	{
		for (auto i : loop::range(0, 1, 2)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0 }));
	}

	SECTION("range(0, 1, 2, true)") 
	{
		for (auto i : loop::range(0, 1, 2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0 }));
	}

	SECTION("range(0, 10, 2)") 
	{
		for (auto i : loop::range(0, 10, 2)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0, 2, 4, 6, 8 }));
	}

	SECTION("range(0, 10, 2, true)") 
	{
		for (auto i : loop::range(0, 10, 2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0, 2, 4, 6, 8, 10 }));
	}

	SECTION("range(0, 9, 2)") 
	{
		for (auto i : loop::range(0, 9, 2)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0, 2, 4, 6, 8 }));
	}

	SECTION("range(0, 9, 2, true)") 
	{
		for (auto i : loop::range(0, 9, 2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 0, 2, 4, 6, 8 }));
	}

	SECTION("range(9, 0, -2)") 
	{
		for (auto i : loop::range(9, 0, -2)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 9, 7, 5, 3, 1 }));
	}

	SECTION("range(9, 0, -2, true)") 
	{
		for (auto i : loop::range(9, 0, -2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 9, 7, 5, 3, 1 }));
	}

	SECTION("range(10, 0, -2)") 
	{
		for (auto i : loop::range(10, 0, -2)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 10, 8, 6, 4, 2 }));
	}

	SECTION("range(10, 0, -2, true)") 
	{
		for (auto i : loop::range(10, 0, -2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 10, 8, 6, 4, 2, 0 }));
	}

	SECTION("range(1, 1, 2, false/true)") 
	{
		for (auto i : loop::range(1, 1, 2)) v.push_back(i);
		REQUIRE(v.size() == 0u);

		for (auto i : loop::range(1, 1, 2, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 1 }));
	}

	SECTION("range(1, 1, 0, false/true)") 
	{
		for (auto i : loop::range(1, 1, 0)) v.push_back(i);
		REQUIRE(v.size() == 0u);

		for (auto i : loop::range(1, 1, 0, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>({ 1 }));
	}

	SECTION("integer range, wrong step direction results in empty loop") 
	{
		for (auto i : loop::range(0, 10, -2)) v.push_back(i);
		REQUIRE(v.size() == 0u);

		for (auto i : loop::range(10, 0, 2)) v.push_back(i);
		REQUIRE(v.size() == 0u);

		for (auto i : loop::range(0, 10, -2, true)) v.push_back(i);
		REQUIRE(v.size() == 0u);

		for (auto i : loop::range(10, 0, 2, true)) v.push_back(i);
		REQUIRE(v.size() == 0u);
	}
}

TEST_CASE("integer range, invalid parameter values", "[intrange]" ) 
{
	std::vector<int> v;
	REQUIRE(v.size() == 0u);

	SECTION("zero step size results in empty loop") 
	{
		for (auto i : loop::range(0, 10, 0)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(10, 0, 0)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(0, 9, 0)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(9, 0, 0)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});
	}

	SECTION("zero step size results in empty loop, also with endpoint") 
	{
		for (auto i : loop::range(0, 10, 0, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(10, 0, 0, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(0, 9, 0, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});

		for (auto i : loop::range(9, 0, 0, true)) v.push_back(i);
		REQUIRE(v == std::vector<int>{});
	}
}
