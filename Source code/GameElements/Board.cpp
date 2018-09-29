#include <Other/Utility.hpp>
#include <RandomNumbers/RandomIntegerGenerator.hpp>
#include "Board.hpp"
#include "Snake.hpp"
#include "GrowBonus.hpp"

Board::Board(const sf::Vector2u & gridsNum, float gridSize, const TextureStorage & textures, GameStatus & gameStatus)
	: mGridsNum(gridsNum),
	mGridSize(gridSize),
	mGameStatus(gameStatus),
	mGrowBonus(textures, *this),
	mSnake(textures, *this, mGrowBonus)
{
	mSnake.setSpeed(0.5f);
}

sf::Vector2i Board::getGridsNum() const
{
	return mGridsNum;
}

float Board::getGridSize() const
{
	return mGridSize;
}

sf::Vector2f Board::getBoardSize() const
{
	return sf::Vector2f(mGridsNum.x * mGridSize, mGridsNum.y * mGridSize);
}

bool Board::isOutOfBoard(const sf::Vector2i & grid) const
{
	if (grid.x < 0 || grid.y < 0 || grid.x >= mGridsNum.x || grid.y >= mGridsNum.y)
		return true;
	return false;
}

sf::Transform Board::getGridTransform(const sf::Vector2i & grid) const
{
	sf::Transform transform = getTransform();
	sf::Vector2f offset(grid.x * mGridSize, grid.y * mGridSize);
	transform.translate(offset);
	return transform;
}

void Board::update(sf::Time deltaTime)
{
	if (mSnake.isFullGrown())
	{
		mGameStatus = GameStatus::gameSuccess;
		return;
	}
	if (!mSnake.isAlive())
	{
		mGameStatus = GameStatus::gameFailure;
		return;
	}
	
	if (mGrowBonus.isEaten())
		generateGrowBonus();

	mSnake.update(deltaTime);
}

void Board::handleEvent(const sf::Event & event)
{
	mSnake.handleEvent(event);
}

void Board::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape background(sf::Vector2f(mGridsNum.x * mGridSize, mGridsNum.y * mGridSize));
	background.setFillColor(sf::Color(50, 50, 50));

	sf::RenderStates backgroundStates = states;
	backgroundStates.transform *= getTransform();
	target.draw(background, backgroundStates);

	target.draw(mSnake, states);
	if (!mGrowBonus.isEaten())
		target.draw(mGrowBonus, states);
}

void Board::generateGrowBonus()
{
	RandomIntegerGenerator<int> randomX(0, mGridsNum.x - 1);
	RandomIntegerGenerator<int> randomY(0, mGridsNum.y - 1);
	sf::Vector2i newBonus(randomX.generateRandom(), randomY.generateRandom());

	while (mSnake.belongsToSnake(newBonus))
	{
		++newBonus.x;
		if (newBonus.x == mGridsNum.x)
		{
			newBonus.x = 0;
			++newBonus.y;
		}
		if (newBonus.y == mGridsNum.y)
			newBonus.y = 0;
	}

	mGrowBonus.setPosition(newBonus);
}
