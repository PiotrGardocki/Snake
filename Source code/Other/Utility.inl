#include <ctime>

namespace
{
	std::mt19937 createEngine()
	{
		//return std::mt19937(std::random_device()());
		return std::mt19937(std::time(nullptr));
	}
	auto Engine = std::move(createEngine());
}

template <typename Resource>
void centerOrigin(Resource & resource)
{
	sf::FloatRect bounds = resource.getLocalBounds();
	resource.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

template<typename T>
T randomInt(const T & min, const T & max)
{
	return std::uniform_int_distribution<T>(min, max)(Engine);
}

template <typename T>
T randomFloat(const T & min, const T & max)
{
	return std::uniform_real_distribution<T>(min, max)(Engine);
}