#ifndef RANDOMREALNUMBERGENERATOR_HPP_
#define RANDOMREALNUMBERGENERATOR_HPP_

#include <type_traits>
#include "RandomGeneratorBase.hpp"

template <typename T>
class RandomRealNumberGenerator : private RandomGeneratorBase
{
	static_assert(std::is_floating_point<T>::value, "RandomRealNumberGenerator has to be floating point type");

    public:
		RandomRealNumberGenerator(const T & min, const T & max);

		void setNewRange(const T & min, const T & max);

		T getMin() const;
		T getMax() const;

		T generateRandom();
		T operator()();

    private:
		std::uniform_real_distribution<T> mRandom;
};

#include "RandomRealNumberGenerator.inl"

#endif // RANDOMREALNUMBERGENERATOR_HPP_