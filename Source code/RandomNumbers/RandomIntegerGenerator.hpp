#ifndef RANDOMINTEGERGENERATOR_HPP_
#define RANDOMINTEGERGENERATOR_HPP_

#include <type_traits>
#include "RandomGeneratorBase.hpp"

template <typename T>
class RandomIntegerGenerator : private RandomGeneratorBase
{
	static_assert(std::is_integral<T>::value, "RandomIntegerGenerator has to be integral type");

    public:
        RandomIntegerGenerator(const T & min, const T & max);

		void setNewRange(const T & min, const T & max);

		T getMin() const;
		T getMax() const;

		T generateRandom();
		T operator()();

    private:
		std::uniform_int_distribution<T> mRandom;
};

#include "RandomIntegerGenerator.inl"

#endif // RANDOMINTEGERGENERATOR_HPP_