#include <complex>
#include <vector>
#include "catch.hpp"
#include "loop.h"

TEST_CASE("linear spaced, valid parameter values", "[linspace]") 
{
	using Vec = std::vector<double>;
	Vec v;

	SECTION("linspace(0., 2., 4) closed") 
	{
		for (auto x : loop::linspace(0., 2., 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);
		REQUIRE(v == Vec({ 0., .5, 1., 1.5, 2. }));
	}

	SECTION("linspace(0., 2., 4) open") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::open)) v.push_back(x);
		REQUIRE(v.size() == 3u);
		REQUIRE(v == Vec({ .5, 1., 1.5 }));
	}

	SECTION("linspace(0., 2., 4) rightopen") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::rightopen)) v.push_back(x);
		REQUIRE(v.size() == 4u);
		REQUIRE(v == Vec({ 0., .5, 1., 1.5 }));
	}

	SECTION("linspace(0., 2., 4) leftopen") 
	{
		for (auto x : loop::linspace(0., 2., 4, loop::boundary::leftopen)) v.push_back(x);
		REQUIRE(v.size() == 4u);
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
		REQUIRE(v == Vec({ 0., 1. }));
	}

	SECTION("linspace(2., 0., 4) closed") 
	{
		for (auto x : loop::linspace(2., 0., 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);
		REQUIRE(v == Vec({ 2., 1.5, 1., .5, 0. }));
	}
	
	SECTION("linspace(1., 2., n) closed") 
	{
		for (int n = 1; n < 100; ++n)
		{
			v.clear();
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

	SECTION("n<1 boundarys results in empty linspace ") 
	{
		for (auto x : loop::linspace(0., 1., 0)) v.push_back(x);
		REQUIRE(v.size() == 0u);
		
		for (auto x : loop::linspace(0., 1., -1)) v.push_back(x);
		REQUIRE(v.size() == 0u);

		// shall not compile:	
		// for (auto x : loop::linspace(0., 1., 0.5)) v.push_back(x);
	}
}

TEST_CASE("linear spaced complex<double> values", "[linspace]") 
{
	using namespace std::literals;
	using Vec = std::vector<std::complex<double>>;
	Vec v;

	SECTION("linspace(0., 2.+1.i, 4) closed") 
	{
		for (auto x : loop::linspace(0., 2.+1.i, 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);
		
		auto expected = Vec({ 0.+0.i, .5+0.25i, 1.+.5i, 1.5+.75i, 2.+1.i });
		REQUIRE(v == expected);
	}
}

TEST_CASE("linear spaced complex<float> values", "[linspace]") 
{
	using namespace std::literals;
	using Vec = std::vector<std::complex<float>>;
	Vec v;

	SECTION("linspace(0., 2.+1.if, 4) closed") 
	{
		for (auto x : loop::linspace(0.f, 2.f+1.if, 4)) v.push_back(x);
		REQUIRE(v.size() == 5u);

		auto expected = Vec{{ 0.f+0.if, .5f+0.25if, 1.f+.5if, 1.5f+.75if, 2.f+1.if }};
		REQUIRE(v == expected);
	}
}

// a simple 3D Vector
struct Vec3D
{
	double x, y, z;

	Vec3D& operator+= (Vec3D v)  { x += v.x; y += v.y; z += v.z; return *this; }
	Vec3D& operator-= (Vec3D v)  { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vec3D& operator*= (double d) { x *= d; y *= d; z *= d; return *this; }
};

Vec3D operator+ (Vec3D u, Vec3D v)  { return u += v; }
Vec3D operator- (Vec3D u, Vec3D v)  { return u -= v; }
Vec3D operator* (Vec3D u, double d) { return u *= d; }
Vec3D operator* (double d, Vec3D v) { return v * d; }

bool operator== (Vec3D u, Vec3D v) { return u.x == v.x && u.y == v.y && u.z == v.z; }
double abs(Vec3D v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

std::ostream& operator<< (std::ostream& os, Vec3D v)
{
	return os << v.x << ' ' << v.y << ' ' << v.z;
}

TEST_CASE("linear spaced simple Vec3D values", "[linspace]") 
{
	using Vec = std::vector<Vec3D>;
	Vec v;

	SECTION("linspace(Vec3D{0, 0, 0}, Vec3D{1, 1, 1}, 2) closed") 
	{
		Vec3D a{ 0, 0, 0 }, b{ 1, 1, 1 };
		for (auto x : loop::linspace(a, b, 2)) v.push_back(x);
		REQUIRE(v.size() == 3u);
		
		auto expected = Vec{ a, (a+b)*0.5, b };
		REQUIRE(v == expected);
	}
}
