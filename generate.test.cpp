// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vector>
#include <string>
#include <complex>
#include "catch.hpp"
#include "loop.h"

TEST_CASE("generic generator for int values", "[intgenerator]" ) 
{
	using Vec = std::vector<int>;
	Vec v;
	REQUIRE(v.size() == 0u);

	SECTION("zero step size results in empty loop") 
	{
		for (auto i : loop::generate(0, 5, 0)) v.push_back(i);
		REQUIRE(v == Vec(5, 0));
	}

	SECTION("generate(0, 5, 1)") 
	{
		for (auto i : loop::generate(0, 5, 1)) v.push_back(i);
		REQUIRE(v == Vec({ 0, 1, 2, 3, 4 }));
	}

	SECTION("generate(4, 5, -1)") 
	{
		for (auto i : loop::generate(4, 5, -1)) v.push_back(i);
		REQUIRE(v == Vec({ 4, 3, 2, 1, 0 }));
	}
	
	SECTION("generate(0, 5, 2)") 
	{
		for (auto i : loop::generate(0, 5, 2)) v.push_back(i);
		REQUIRE(v == Vec({ 0, 2, 4, 6, 8 }));
	}

	SECTION("generate(8, 5, -2)") 
	{
		for (auto i : loop::generate(8, 5, -2)) v.push_back(i);
		REQUIRE(v == Vec({ 8, 6, 4, 2, 0 }));
	}
}

TEST_CASE("generic generator for string values", "[stringgenerator]" ) 
{
	using namespace std::string_literals;
	using Vec = std::vector<std::string>;
	Vec v;
	REQUIRE(v.size() == 0u);

	SECTION("generate string sequence") 
	{
		for (auto i : loop::generate("|"s, 3, "=")) v.push_back(i);
		REQUIRE(v == Vec({ "|", "|=", "|==" }));
	}
}

TEST_CASE("generic generator for complex values", "[complexgenerator]" ) 
{
	using namespace std::complex_literals;
	using Vec = std::vector<std::complex<double>>;
	Vec v;
	REQUIRE(v.size() == 0u);

	SECTION("generate complex sequence") 
	{
		for (auto i : loop::generate(2.-1.i, 3, 1.i)) v.push_back(i);
		REQUIRE(v == Vec({ 2.-1.i, 2.0+0.i, 2.0+1.i }));
	}
}

