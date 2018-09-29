#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <deque>
#include <SFML/Graphics.hpp>
#include <ResourceStorage/ResourceStorage.hpp>

class Board;
class GrowBonus;

class Snake : public sf::Drawable
{
    public:
        Snake(const TextureStorage & textures, const Board & board, GrowBonus & growBonus);
		
		void setSpeed(float speed);

		bool isFullGrown() const;
		bool isAlive() const;
		bool belongsToSnake(const sf::Vector2i & grid) const;

		void update(sf::Time deltaTime);
		void handleEvent(const sf::Event & event);

    private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		void setSpriteScaleAndPosition() const;

		bool checkIfSnakeHitItself(const sf::Vector2i & newHeadPosition);
		void checkIfSnakeAteBonus();
		void createNewHead(const sf::Vector2i position);
		sf::Vector2i getHeadMovedByOneGrid() const;

		enum ElementType
		{
			head,
			bodyStraight,
			bodyTurned,
			tail
		};
		enum Direction
		{
			up,
			right,
			down,
			left
		};
		struct SnakeElement
		{
			ElementType type;
			Direction direction;
			sf::Vector2i position;
		};

		static float getNormalRotation(Direction direction);
		static float getTurnedBodyRotation(std::deque<SnakeElement>::const_iterator element);
		const sf::Texture & getTexture(ElementType elementType) const;

		void createInitialSnake();

		SnakeElement createInitialHead(const sf::Vector2i & position) const;
		SnakeElement createInitialBody(const sf::Vector2i & position) const;
		SnakeElement createInitialTail(const sf::Vector2i & position) const;

	private:
		const Board & mBoard;
		float mTotalTime;
		float mSpeed;  // seconds per grid
		bool mIsAlive;
		GrowBonus & mGrowBonus;

		Direction mNextDirection;
		std::deque<SnakeElement> mSnake;

		const sf::Texture & mHeadTexture;
		const sf::Texture & mBodyStraightTexture;
		const sf::Texture & mBodyTurnedTexture;
		const sf::Texture & mTailTexture;
		mutable sf::Sprite mSprite;
};

#endif // SNAKE_HPP_
