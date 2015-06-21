#ifndef LOOP_RANGE_H
#define LOOP_RANGE_H

#include <cmath>
#include <type_traits>
#include <iterator>

namespace loop {

// ---[ integral ranges ]----------------------------------

namespace detail {

template <typename T, typename N, typename Increment>
class RangeGenerator		
{
public: 
	RangeGenerator(T start, N n, Increment step) 
	: start_(start), n_(n), step_(step)
	{
	}
	
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		iterator() : n_(0) {}
		iterator(T v, N n, Increment s) : v_(v), n_(n), s_(s) {}

		bool operator==(const iterator& rhs) const { return n_ == rhs.n_; }
		bool operator!=(const iterator& rhs) const { return !(*this == rhs); }

		iterator& operator++()      { v_ += s_; --n_; return *this; }
		iterator  operator++(int)   { auto tmp = *this; ++(*this); return tmp; }
		auto      operator*() const { return v_; }
	private:
		T v_;
		N n_;
		Increment s_;	
	};

	iterator begin() const { return { start_, n_, step_ }; }
	iterator end()   const { return {}; }
private: 
	T start_;
	N n_;
	Increment step_;
};

} // end namespace detail

template <typename Start, typename N, typename Increment>
auto generate(Start start, N n, Increment step) 
{
	static_assert(std::is_integral<N>::value, "integral type required");
	return detail::RangeGenerator<Start, N, Increment>{ start, n, step };
}

template <typename Start, typename End, typename Increment>
auto range(Start start, End end, Increment step, bool with_end = false) 
{
	using Domain = std::common_type_t<Start, End, Increment>;
	using N = std::common_type_t<Domain, std::size_t>;
	
	static_assert(std::is_integral<Domain>::value, "integral type required");

	Domain a = start, b = end;	
	N n = a == b && with_end;
	
	if (step != 0 && (b < a) == (step < 0))
	{
		n = b < a ? a - b : b - a;
		Increment abs_step = step > 0 ? step : -step;

		if (abs_step != 1) n /= abs_step;
		if (with_end) ++n;
		else if (Domain(a + n*step) != b) ++n;
	}
	
	return generate(a, n, step);
}

template <typename Start, typename End>
auto range(Start start, End end) { return range(start, end, 1); }

template <typename N>
auto range(N n) { return range(N{}, n); }

template <typename N>
auto countdown(N n) { return range((n ? n-1 : 0), 0, -1, n != 0); }

// ---[ non-integral, interpolated ranges ]----------------------------------

namespace detail {

template <typename Domain, typename N>
class LinearGenerator
{
	static auto scalar(N n)
	{
		using std::abs;
		using ScalarType = decltype(abs(Domain{}));
		return static_cast<ScalarType>(n);
	}
	
public:

	LinearGenerator(Domain a, Domain b, N n, N first, N last)
	: a_(a), dx_((b-a)*(1/scalar(n))), first_(first), last_(last)
	{
	}

	class iterator : public std::iterator<std::forward_iterator_tag, Domain>
	{
	public:
		iterator() : i_(0) {}
		iterator(Domain a, Domain dx, N i)
		: a_(a), dx_(dx), i_(i) 
		{
		}

		bool operator==(const iterator& rhs) const { return i_ == rhs.i_; }
		bool operator!=(const iterator& rhs) const { return !(*this == rhs); }

		iterator& operator++()      { ++i_; return *this; }
		iterator  operator++(int)   { auto tmp = *this; ++(*this); return tmp; }
		auto      operator*() const { return a_ + scalar(i_) * dx_; }
	private:
		Domain a_, dx_;
		N i_;	
	};

	iterator begin() const { return { a_, dx_, first_ }; }
	iterator end()   const { return { a_, dx_, last_ + 1 }; }
private:
	Domain a_, dx_;
	N first_, last_;
};

} // end namespace detail

enum class boundary { closed, rightopen, leftopen, open };

template <typename Start, typename End, typename N>
auto linspace(Start a, End b, N n, boundary type = boundary::closed)
{
	using Domain = decltype(a + (b - a)); 
	static_assert(!std::is_integral<Domain>::value, "use non-integral [a,b]");
	static_assert(std::is_integral<N>::value,       "use integral n");

	if (n < 1) 
	{
		n = 1;
		type = boundary::open;
	}
	
	bool without_start = type == boundary::open || type == boundary::leftopen;
	bool without_end   = type == boundary::open || type == boundary::rightopen;

	N first = without_start;
	N last  = n - without_end;
	
	return detail::LinearGenerator<Domain, N>(a, b, n, first, last);
}

} // end namespace loop

#endif // LOOP_RANGE_H
