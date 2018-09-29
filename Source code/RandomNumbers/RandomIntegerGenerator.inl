template<typename T>
RandomIntegerGenerator<T>::RandomIntegerGenerator(const T & min, const T & max)
	: mRandom(min, max)
{
}

template<typename T>
void RandomIntegerGenerator<T>::setNewRange(const T & min, const T & max)
{
	mRandom = std::uniform_int_distribution<T>(min, max);
}

template<typename T>
T RandomIntegerGenerator<T>::getMin() const
{
	return mRandom.min();
}

template<typename T>
T RandomIntegerGenerator<T>::getMax() const
{
	return mRandom.max();
}

template<typename T>
T RandomIntegerGenerator<T>::generateRandom()
{
	return mRandom(getEngine());
}

template<typename T>
inline T RandomIntegerGenerator<T>::operator()()
{
	return mRandom(getEngine());
}
