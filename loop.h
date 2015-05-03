#ifndef LOOP_RANGE_H
#define LOOP_RANGE_H

#include <type_traits>
#include <iterator>

namespace loop {

// ---[ integral ranges ]----------------------------------

namespace detail {

template <typename T, typename N, typename Increment>
class Range		
{
public: 
	Range(T start, N n, Increment step) 
	: start_(start), n_(n), step_(step)
	{
	}
	
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
	public:
		iterator() : n_(0) {}
		iterator(T v, N n, Increment s) : v_(v), n_(n), s_(s) {}

		auto operator*() const { return v_; }
		auto operator++() { v_ += s_; --n_; return *this; }
		auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		bool operator==(iterator rhs) const { return n_ == rhs.n_; }
		bool operator!=(iterator rhs) const { return !(*this == rhs); }
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

template <typename X, typename U>
class CommonType
{
	using X1 = typename std::remove_reference<X>::type;
	using U1 = typename std::remove_reference<U>::type;
public:
	using type = decltype(X1() + U1());
};

template <typename T>
class CommonType<T, T>
{
public:
	using type = typename std::remove_reference<T>::type;
};

} // end namespace detail

template <typename Start, typename End, typename Increment>
auto range(Start start, End end, Increment step, bool include_end = false) 
{
	using Domain = typename detail::CommonType<Start, End>::type;
	using N = typename detail::CommonType<Domain, size_t>::type;
	
	static_assert(std::is_integral<Domain>::value, "integral type required");

	Domain a = start, b = end;	
	N n = a == b && include_end;
	
	if (step != 0 && (b < a) == (step < 0))
	{
		n = b < a ? a - b : b - a;
		Increment abs_step = step > 0 ? step : -step;

		if (abs_step != 1) n /= abs_step;
		if (include_end) ++n;
		else if (Domain(a + n*step) != b) ++n;
	}
	
	return detail::Range<Domain, N, Increment>{ a, n, step };
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
class LinearInterpolatedRange
{
public:
	LinearInterpolatedRange(Domain a, Domain b, N n, N first, N last)
	: a_(a), dx_((b-a)/n), n_(n), first_(first), last_(last)
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

		auto operator*() const { return a_ + i_ * dx_; }
		auto operator++() { ++i_; return *this; }
		auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		bool operator==(iterator rhs) const { return i_ == rhs.i_; }
		bool operator!=(iterator rhs) const { return !(*this == rhs); }
	private:
		Domain a_, dx_;
		N i_;	
	};

	iterator begin() const { return { a_, dx_, first_ }; }
	iterator end()   const { return { a_, dx_, last_ + 1 }; }
private:
	Domain a_, dx_;
	N n_, first_, last_;
};

} // namespace detail

enum class boundary { closed, rightopen, leftopen, open };

template <typename Start, typename End, typename N>
auto linspace(Start a, End b, N steps, boundary type = boundary::closed)
{
	static_assert(std::is_integral<N>::value, 
		"integral boundary step counter required");	

	using Domain = decltype(a + (b - a) / steps * steps); 
	static_assert(!std::is_integral<Domain>::value, 
		"non-integral type boundaries values required");

	if (steps < 1) 
	{
		steps = 1;
		type = boundary::open;
		b = static_cast<End>(a);
	}
	
	bool without_start = type == boundary::open || type == boundary::leftopen;
	bool without_end   = type == boundary::open || type == boundary::rightopen;

	N first = without_start;
	N last  = steps - without_end;
	return detail::LinearInterpolatedRange<Domain, N>(a, b, steps, first, last);
}

} // end namespace loop

#endif // LOOP_RANGE_H
