#ifndef RESOURCESTORAGE_HPP_
#define RESOURCESTORAGE_HPP_

#include <map>
#include <string>
#include <memory>
#include <utility>
#include "ResourceIdentifiers.hpp"

namespace sf
{
	class Texture;
	class Font;
}

template <typename Identifier, typename Resource>
class ResourceStorage
{
    public:
		void load(Identifier id, const std::string & filename);
		Resource & get(Identifier id);
		const Resource & get(Identifier id) const;

    private:
		std::map<Identifier, std::unique_ptr<Resource>> mResources;
};

template<>
void ResourceStorage<Textures::ID, sf::Texture>::load(Textures::ID id, const std::string & filename);

#include "ResourceStorage.inl"

using TextureStorage = ResourceStorage<Textures::ID, sf::Texture>;
using FontStorage = ResourceStorage<Fonts::ID, sf::Font>;

#endif // RESOURCESTORAGE_HPP_