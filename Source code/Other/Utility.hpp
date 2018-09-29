#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <SFML/Graphics.hpp>
#include <random>
#include <utility>

template <typename Resource>
void centerOrigin(Resource & resource);

template <typename T>
T randomInt(const T & min, const T & max);

template <typename T>
T randomFloat(const T & min, const T & max);

#include "Utility.inl"

#endif // !UTILITY_HPP_
