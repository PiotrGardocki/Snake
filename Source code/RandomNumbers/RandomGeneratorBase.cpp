#include <chrono>
#include "RandomGeneratorBase.hpp"

namespace
{
	long long createSeed()
	{
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		return seed;
	}
}

thread_local std::mt19937 RandomGeneratorBase::mEngine(createSeed());

std::mt19937 & RandomGeneratorBase::getEngine() const
{
	return mEngine;
}
