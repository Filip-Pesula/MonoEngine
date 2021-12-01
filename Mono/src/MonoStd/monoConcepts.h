#pragma once
#include <concepts>
namespace mono {
	template<typename T>
	concept Aritmetic_ = requires (T x) {
		x + x;
		x - x;
		x * x;
		x / x;
		x = x;
	};
	template<typename T, typename F> 
	concept Scalar_f_ = requires (T x, std::is_floating_point<F> a) {
		x * a;
	};
	template<typename T, typename F>
	concept Scalar_ = requires (T x, F a) {
		x * a;
	};

}