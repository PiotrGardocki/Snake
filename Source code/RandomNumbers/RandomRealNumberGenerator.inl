template<typename T>
RandomRealNumberGenerator<T>::RandomRealNumberGenerator(const T & min, const T & max)
	: mRandom(min, max)
{
}

template<typename T>
void RandomRealNumberGenerator<T>::setNewRange(const T & min, const T & max)
{
	mRandom = std::uniform_real_distribution<T>(min, max);
}

template<typename T>
T RandomRealNumberGenerator<T>::getMin() const
{
	return mRandom.min();
}

template<typename T>
T RandomRealNumberGenerator<T>::getMax() const
{
	return mRandom.max();
}

template<typename T>
T RandomRealNumberGenerator<T>::generateRandom()
{
	return mRandom(getEngine());
}

template<typename T>
T RandomRealNumberGenerator<T>::operator()()
{
	return mRandom(getEngine());
}