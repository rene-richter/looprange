// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include "catch.hpp"
#include "loop.h"

TEST_CASE("linear spaced, valid parameter values", "[linspace]") 
{
	using Vec = std::vector<double>;
	Vec v;
	REQUIRE(v.size() == 0u);

	SECTION("linspace(0., 2., 4) closed") 
	{
		for (auto x : loop::linspace(0., 2., 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);
		REQUIRE(v.front() == 0.);
		REQUIRE(v.back() == 2.);
		REQUIRE(v == Vec({ 0., .5, 1., 1.5, 2. }));
	}

	SECTION("linspace(0., 2., 4) open") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::open)) v.push_back(x);
		REQUIRE(v.size() == 3u);
		REQUIRE(v.front() == 0.5);
		REQUIRE(v.back() == 1.5);
		REQUIRE(v == Vec({ .5, 1., 1.5 }));
	}

	SECTION("linspace(0., 2., 4) rightopen") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::rightopen)) v.push_back(x);
		REQUIRE(v.size() == 4u);
		REQUIRE(v.front() == 0.);
		REQUIRE(v.back() == 1.5);
		REQUIRE(v == Vec({ 0., .5, 1., 1.5 }));
	}

	SECTION("linspace(0., 2., 4) leftopen") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::leftopen)) v.push_back(x);
		REQUIRE(v.size() == 4u);
		REQUIRE(v.front() == .5);
		REQUIRE(v.back() == 2.);
		REQUIRE(v == Vec({ .5, 1., 1.5, 2. }));
	}

	SECTION("linspace(0., 1., 3) open") 
	{
		for (auto x : loop::linspace(0., 1., 3)) v.push_back(x);
		REQUIRE(v.size() == 4u);
		REQUIRE(v.front() == 0.);
		REQUIRE(v.back() == 1.);
		REQUIRE(v == Vec({ 0., 1/3., 2/3., 1. }));
	}

	SECTION("linspace(0., 1., 1) closed") 
	{
		for (auto x : loop::linspace(0., 1., 1)) v.push_back(x);
		REQUIRE(v.size() == 2u);
		REQUIRE(v.front() == 0.);
		REQUIRE(v.back() == 1.);
		REQUIRE(v == Vec({ 0., 1. }));
	}

	SECTION("linspace(2., 0., 4) closed") 
	{
		for (auto x : loop::linspace(2., 0., 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);
		REQUIRE(v.front() == 2.);
		REQUIRE(v.back() == 0.);
		REQUIRE(v == Vec({ 2., 1.5, 1., .5, 0. }));
	}
	
	SECTION("linspace(1., 2., n) closed") 
	{
		for (int n = 1; n < 100; ++n)
		{
			v.clear();
			REQUIRE(v.size() == 0u);
			INFO("n = " << n);

			for (auto x : loop::linspace(1., 2., n)) v.push_back(x);
			REQUIRE(v.size() == size_t(n + 1));
			REQUIRE(v.front() == 1.);
			REQUIRE(v[1] == Approx(v[0] + 1./n));
			REQUIRE(v.back() == 2.);
		}	
	}
}

TEST_CASE("linear spaced, invalid parameter values", "[linspace]") 
{
	using Vec = std::vector<double>;
	Vec v;
	REQUIRE(v.size() == 0u);

	SECTION("n<1 boundarys results in empty linspace ") 
	{
		for (auto x : loop::linspace(0., 1., 0)) v.push_back(x);
		REQUIRE(v.size() == 0u);
		
		for (auto x : loop::linspace(0., 1., -1)) v.push_back(x);
		REQUIRE(v.size() == 0u);

		// should fail to compile:	
		// for (auto x : loop::linspace(0., 1., 0.5)) v.push_back(x);
	}
}
