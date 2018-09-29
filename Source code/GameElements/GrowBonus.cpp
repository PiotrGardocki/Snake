#include "GrowBonus.hpp"
#include "Board.hpp"

GrowBonus::GrowBonus(const TextureStorage & textures, const Board & board)
	: mBoard(board),
	mIsEaten(true),
	mSprite(textures.get(Textures::growBonus))
{
	float scaleX = board.getGridSize() / mSprite.getTextureRect().width;
	float scaleY = board.getGridSize() / mSprite.getTextureRect().height;

	mSprite.setScale(scaleX, scaleY);
}

void GrowBonus::setPosition(const sf::Vector2i & position)
{
	mPosition = position;
	mIsEaten = false;
}

sf::Vector2i GrowBonus::getPosition() const
{
	return mPosition;
}

void GrowBonus::eat()
{
	mIsEaten = true;
}

bool GrowBonus::isEaten() const
{
	return mIsEaten;
}

void GrowBonus::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= mBoard.getGridTransform(mPosition);
	target.draw(mSprite, states);
}
