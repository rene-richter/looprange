#ifndef LOOP_RANGE_H
#define LOOP_RANGE_H

#include <type_traits>
#include <iterator>

namespace loop {

// ---[ integral ranges ]----------------------------------

namespace detail {

template <typename Value, typename N, typename Increment>
class Range		
{
public: 
	Range(Value start, N n, Increment step) 
	: start_(start), n_(n), step_(step)
	{
	}
	
	class iterator : public std::iterator<std::forward_iterator_tag, Value>
	{
	public:
		iterator() : n_(0) {}
		iterator(Value v, N n, Increment s) : v_(v), n_(n), s_(s) {}

		auto operator*() const { return v_; }
		auto operator++() { v_ += s_; --n_; return *this; }
		auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		bool operator==(iterator rhs) const { return n_ == rhs.n_; }
		bool operator!=(iterator rhs) const { return !(*this == rhs); }
	private:
		Value v_;
		N n_;
		Increment s_;	
	};

	iterator begin() const { return { start_, n_, step_ }; }
	iterator end()   const { return {}; }
private: 
	Value start_;
	N n_;
	Increment step_;
};

} // end namespace detail

template <typename Start, typename End, typename Increment>
auto range(Start start, End end, Increment step, bool include_end = false) 
{
	auto n = step ? (end - start) / step : 0;
	static_assert(std::is_integral<decltype(n)>::value, 
		"integral counter required");

	if (n < 0 || (step == 0 && start != end)) n = 0;
	else if (include_end || start + n * step != end) ++n;	
	return detail::Range<Start, decltype(n), Increment>{ start, n, step };
}

template <typename Start, typename End>
auto range(Start start, End end) { return range(start, end, 1); }

template <typename End>
auto range(End end) { return range(End(0), end); }

template <typename End>
auto range_down(End end) { return range(end - 1, End(0), -1, true); }

// ---[ non-integral, interpolated ranges ]----------------------------------

namespace detail {

template <typename Value, typename N>
class LinearInterpolatedRange
{
public:
	LinearInterpolatedRange(Value a, Value b, N n, N first, N last)
	: a_(a), dx_((b-a)/n), n_(n), first_(first), last_(last)
	{
	}

	class iterator : public std::iterator<std::forward_iterator_tag, Value>
	{
	public:
		iterator() : i_(0) {}
		iterator(Value a, Value dx, N i)
		: a_(a), dx_(dx), i_(i) 
		{
		}

		auto operator*() const { return a_ + i_ * dx_; }
		auto operator++() { ++i_; return *this; }
		auto operator++(int) { auto tmp = *this; ++(*this); return tmp; }

		bool operator==(iterator rhs) const { return i_ == rhs.i_; }
		bool operator!=(iterator rhs) const { return !(*this == rhs); }
	private:
		Value a_, dx_;
		N i_;	
	};

	iterator begin() const { return { a_, dx_, first_ }; }
	iterator end()   const { return { a_, dx_, last_ + 1 }; }
private:
	Value a_, dx_;
	N n_, first_, last_;
};

} // namespace detail

enum class interval { closed, rightopen, leftopen, open };

template <typename Start, typename End, typename N>
auto linrange(Start a, End b, N steps, interval type = interval::closed)
{
	static_assert(std::is_integral<N>::value, 
		"integral interval step counter required");	

	using Value = decltype(a + (b - a) / steps * steps); 
	static_assert(!std::is_integral<Value>::value, 
		"non-integral type boundaries values required");

	if (steps < 1) 
	{
		steps = 1;
		type = interval::open;
		b = static_cast<End>(a);
	}
	
	bool without_start = type == interval::open || type == interval::leftopen;
	bool without_end   = type == interval::open || type == interval::rightopen;

	N first = without_start;
	N last  = steps - without_end;
	return detail::LinearInterpolatedRange<Value, N>(a, b, steps, first, last);
}

} // end namespace loop

#endif // LOOP_RANGE_H
