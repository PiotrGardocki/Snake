#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <SFML/Graphics.hpp>
#include <ResourceStorage/ResourceStorage.hpp>
#include "GameStatus.hpp"
#include "Snake.hpp"
#include "GrowBonus.hpp"

class Board : public sf::Drawable, public sf::Transformable
{
    public:
        Board(const sf::Vector2u & gridsNum, float gridSize, const TextureStorage & textures, GameStatus & gameStatus);

		sf::Vector2i getGridsNum() const;
		float getGridSize() const;
		sf::Vector2f getBoardSize() const;
		bool isOutOfBoard(const sf::Vector2i & grid) const;
		sf::Transform getGridTransform(const sf::Vector2i & grid) const;

		void update(sf::Time deltaTime);
		void handleEvent(const sf::Event & event);

	private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		void generateGrowBonus();

    private:
		sf::Vector2i mGridsNum;
		float mGridSize;

		GameStatus & mGameStatus;
		GrowBonus mGrowBonus;
		Snake mSnake;
};

#endif // BOARD_HPP_
