#include <SFML/Graphics.hpp>
#include "ResourceStorage.hpp"

template<>
void ResourceStorage<Textures::ID, sf::Texture>::load(Textures::ID id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> resource(new sf::Texture());
	resource->loadFromFile(filename);
	resource->setSmooth(true);
	mResources.insert(std::make_pair(id, std::move(resource)));
}