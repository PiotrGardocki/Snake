#include "Utility.hpp"

sf::FloatRect getViewRect(const sf::View & view)
{
	sf::Vector2f center = view.getCenter();
	sf::Vector2f size = view.getSize();

	return sf::FloatRect(center - (size/2.f), size);
}
