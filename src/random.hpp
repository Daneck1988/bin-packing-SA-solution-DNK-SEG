#ifndef RANDOM_HPP_RANDOMNESS_WHATEVER_HEADER_238947837827_H
#define RANDOM_HPP_RANDOMNESS_WHATEVER_HEADER_238947837827_H

#include <random>

namespace rng {
	extern std::mt19937_64 rng;

	template<long long start, long long end>
	auto random_int() -> int
	{
		static std::uniform_int_distribution<> rint(start, end);
		return rint(rng);
	}

	template<int start, int end>
	auto random_double() -> double
	{
		static std::uniform_real_distribution<> rdouble(start, end);
		return rdouble(rng);
	}
} // namespace rng

#endif
