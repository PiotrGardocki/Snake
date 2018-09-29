#ifndef GROWBONUS_HPP_
#define GROWBONUS_HPP_

#include <SFML/Graphics.hpp>
#include <ResourceStorage/ResourceStorage.hpp>

class Board;

class GrowBonus : public sf::Drawable
{
    public:
		GrowBonus(const TextureStorage & textures, const Board & board);

		void setPosition(const sf::Vector2i & position);
		sf::Vector2i getPosition() const;

		void eat();
		bool isEaten() const;

    private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

	private:
		const Board & mBoard;

		sf::Vector2i mPosition;
		bool mIsEaten;

		sf::Sprite mSprite;
};

#endif // GROWBONUS_HPP_
