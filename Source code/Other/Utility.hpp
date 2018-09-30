#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <SFML/Graphics.hpp>
#include <utility>

template <typename Resource>
void centerOrigin(Resource & resource);

sf::FloatRect getViewRect(const sf::View & view);

#include "Utility.inl"

#endif // !UTILITY_HPP_
