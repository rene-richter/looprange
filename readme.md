# loop.h - lazy generated range-based for values

This header-only library provides lazy generated values for floating-point, integral and other types in C++14.

# Easy to install and use

* Download `loop.h` and `#include` it into your project. 
* Write range-based for loop (see below).
* Compile as C++14 or higher (g++ or clang with option -std=c++14).
```
#include "loop.h"
// ...
using namespace loop;

for (auto x : linspace(0, 1.0, 4))     ... // 0 0.25 0.5 0.75 1

for (auto i : countdown(5))            ... // 4 3 2 1 0
for (auto i : range(5))                ... // 0 1 2 3 4
for (auto i : range(0, 5))             ... // 0 1 2 3 4
for (auto i : range(0, 6, 2))          ... // 0 2 4
for (auto i : range(0, 6, 2, true))    ... // 0 2 4 6
for (auto i : range(5, 0, -1))         ... // 5 4 3 2 1

using namespace std::string_literals;
for (auto x : generate("I"s, 5, "E")) ... // : I IE IEE IEEE IEEEE
```
See also: loop.demo.cpp

# A more detailed documentation
## Equispaced floating-point values 

```
using namespace loop;

for (auto x : linspace(0, 1.0, 4)) ... // 0 0.25 0.5 0.75 1
for (auto x : linspace(1.0, 0, 4)) ... // 1 0.75 0.5 0.25 0

for (auto x : linspace(0, 1.0, 4, boundary::closed))    ... // 0 0.25 0.5 0.75 1
for (auto x : linspace(0, 1.0, 4, boundary::rightopen)) ... // 0 0.25 0.5 0.75
for (auto x : linspace(0, 1.0, 4, boundary::leftopen))  ... // 0.25 0.5 0.75 1
for (auto x : linspace(0, 1.0, 4, boundary::open))      ... // 0.25 0.5 0.75
```
See also: MATLAB, Numpy 
## generic loop generator

```
using namespace loop;

for (auto x : generate(4, 5, -1))                 ... // 4 3 2 1 0
for (auto x : generate(std::string("O"), 5, "i")) ... // : O Oi Oii Oiii Oiiii
```
See also: Semenov

## Integral values range based for loops
```
using namespace loop;

for (auto i : range(0, 5))          ... // 0 1 2 3 4
for (auto i : range(5, 0, -1))      ... // 5 4 3 2 1
for (auto i : range(0, 6, 2, true)) ... // 0 2 4 6
for (auto i : countdown(5))         ... // 4 3 2 1 0
```

Index für Standard-Container, z.B. `std::vector<T> v`:
```
for (auto i : range(v.size())     ... // 0 ... v.size()-1 
for (auto i : range(3, v.size())  ... // 3 ... v.size()-1 
for (auto i : countdown(v.size()) ... // v.size()-1 ... 0
```

mixed signed/unsigned parameters allowed

See also: Boost irange, cppitertools

## Links & other libraries

* Numpy
* Matlab
* Boost irange
* [cppitertools](https://github.com/ryanhaining/cppitertools) 
* [Mikhail Semenov](http://www.codeproject.com/Articles/876156/Convenient-Constructs-For-Stepping-Through-a-Range) : Convenient Constructs For Stepping Through a Range.

# TODO, known bugs, limitations
* C++11 not supported
* Test other compilers
* linspace() for complex type, linear algebra types (3D vectors etc.)?
* range(0, max_size_t, 1, true) is empty
