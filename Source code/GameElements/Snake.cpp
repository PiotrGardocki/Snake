#include "Snake.hpp"
#include "Board.hpp"
#include "GrowBonus.hpp"

Snake::Snake(const TextureStorage & textures, const Board & board, GrowBonus & growBonus)
	: mBoard(board),
	mTotalTime(0.f),
	mSpeed(0.f),
	mIsAlive(true),
	mGrowBonus(growBonus),
	mHeadTexture(textures.get(Textures::snakeHead)),
	mBodyStraightTexture(textures.get(Textures::snakeBodyStraight)),
	mBodyTurnedTexture(textures.get(Textures::snakeBodyTurned)),
	mTailTexture(textures.get(Textures::snakeTail))
{
	createInitialSnake();
}

void Snake::setSpeed(float speed)
{
	mSpeed = speed;
}

bool Snake::isFullGrown() const
{
	sf::Vector2i boardSize = mBoard.getGridsNum();
	return mSnake.size() == boardSize.x * boardSize.y;
}

bool Snake::isAlive() const
{
	return mIsAlive;
}

bool Snake::belongsToSnake(const sf::Vector2i & grid) const
{
	for (auto & snakeGrid : mSnake)
		if (snakeGrid.position == grid)
			return true;
	return false;
}

void Snake::update(sf::Time deltaTime)
{
	mTotalTime += deltaTime.asSeconds();

	if (isFullGrown() || !isAlive())
		return;

	if (mTotalTime >= mSpeed)
	{
		mTotalTime -= mSpeed;

		sf::Vector2i headPosition(getHeadMovedByOneGrid());

		if (mBoard.isOutOfBoard(headPosition) || checkIfSnakeHitItself(headPosition))
		{
			mIsAlive = false;
			return;
		}

		createNewHead(headPosition);

		checkIfSnakeAteBonus();
	}
}

void Snake::handleEvent(const sf::Event & event)
{
	Direction & currentDirection = mSnake.front().direction;

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			if (currentDirection != Direction::down)
				mNextDirection = up;
			break;
		case sf::Keyboard::Down:
			if (currentDirection != Direction::up)
				mNextDirection = down;
			break;
		case sf::Keyboard::Left:
			if (currentDirection != Direction::right)
				mNextDirection = left;
			break;
		case sf::Keyboard::Right:
			if (currentDirection != Direction::left)
				mNextDirection = right;
			break;
		}
	}
}

void Snake::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	const sf::RenderStates defaultStates(states);

	for (auto element = mSnake.cbegin(); element != mSnake.cend(); ++element)
	{
		mSprite.setTexture(getTexture(element->type));
		setSpriteScaleAndPosition();

		if (element->type == ElementType::bodyTurned)
			mSprite.setRotation(getTurnedBodyRotation(element));
		else
			mSprite.setRotation(getNormalRotation(element->direction));

		states = defaultStates;
		states.transform *= mBoard.getGridTransform(element->position);
		target.draw(mSprite, states);
	}
}

void Snake::setSpriteScaleAndPosition() const
{
	float scaleX = mBoard.getGridSize() / mSprite.getTextureRect().width;
	float scaleY = mBoard.getGridSize() / mSprite.getTextureRect().height;
	mSprite.setScale(scaleX, scaleY);

	sf::FloatRect size = mSprite.getLocalBounds();
	mSprite.setOrigin(size.width / 2.f, size.height / 2.f);
	mSprite.setPosition(size.width * scaleX / 2.f, size.height * scaleY / 2.f);
}

bool Snake::checkIfSnakeHitItself(const sf::Vector2i & newHeadPosition)
{
	for (auto & snakeGrid : mSnake)
		if (snakeGrid.position == newHeadPosition && snakeGrid.type != Snake::tail)
			return true;

	return false;
}

void Snake::checkIfSnakeAteBonus()
{
	if (mGrowBonus.getPosition() == mSnake.front().position)
	{
		mGrowBonus.eat();
	}
	else
	{
		mSnake.pop_back();
		mSnake.back().type = ElementType::tail;
	}
}

void Snake::createNewHead(const sf::Vector2i position)
{
	mSnake.front().direction = mNextDirection;
	if (mSnake[1].direction == mNextDirection)
		mSnake.front().type = ElementType::bodyStraight;
	else
		mSnake.front().type = ElementType::bodyTurned;

	SnakeElement newHead;
	newHead.type = ElementType::head;
	newHead.direction = mNextDirection;
	newHead.position = position;

	mSnake.push_front(newHead);
}

sf::Vector2i Snake::getHeadMovedByOneGrid() const
{
	sf::Vector2i headPosition = mSnake.front().position;
	
	switch (mNextDirection)
	{
	case Snake::up:
		--headPosition.y;
		break;
	case Snake::right:
		++headPosition.x;
		break;
	case Snake::down:
		++headPosition.y;
		break;
	case Snake::left:
		--headPosition.x;
		break;
	}

	return headPosition;
}

float Snake::getNormalRotation(Direction direction)
{
	switch (direction)
	{
	case Direction::up:
		return 0.f;
	case Direction::right:
		return 90.f;
	case Direction::down:
		return 180.f;
	case Direction::left:
		return 270.f;
	}
}

float Snake::getTurnedBodyRotation(std::deque<SnakeElement>::const_iterator element)
{
	auto previousElement = element;
	++previousElement;
	Direction previousDirection = previousElement->direction;

	if ((element->direction == Direction::left  && previousDirection == Direction::up)    || (element->direction == Direction::down  && previousDirection == Direction::right))
		return 0.f;

	if ((element->direction == Direction::up    && previousDirection == Direction::right) || (element->direction == Direction::left  && previousDirection == Direction::down))
		return 90.f;

	if ((element->direction == Direction::up    && previousDirection == Direction::left)  || (element->direction == Direction::right && previousDirection == Direction::down))
		return 180.f;

	if ((element->direction == Direction::right && previousDirection == Direction::up)    || (element->direction == Direction::down  && previousDirection == Direction::left))
		return 270.f;
}

const sf::Texture & Snake::getTexture(ElementType elementType) const
{
	switch (elementType)
	{
	case Snake::head:
		return mHeadTexture;
	case Snake::bodyStraight:
		return mBodyStraightTexture;
	case Snake::bodyTurned:
		return mBodyTurnedTexture;
	case Snake::tail:
		return mTailTexture;
	}
}

void Snake::createInitialSnake()
{
	// board height at least 5 grids
	sf::Vector2i snakePosition = mBoard.getGridsNum();
	snakePosition.x /= 2;
	snakePosition.y /= 2;

	mSnake.push_back(createInitialHead(snakePosition));

	++snakePosition.y;
	mSnake.push_back(createInitialBody(snakePosition));

	++snakePosition.y;
	mSnake.push_back(createInitialTail(snakePosition));
}

Snake::SnakeElement Snake::createInitialHead(const sf::Vector2i & position) const
{
	SnakeElement head;
	head.type = ElementType::head;
	head.direction = Direction::up;
	head.position = position;

	return head;
}

Snake::SnakeElement Snake::createInitialBody(const sf::Vector2i & position) const
{
	SnakeElement body;
	body.type = ElementType::bodyStraight;
	body.direction = Direction::up;
	body.position = position;

	return body;
}

Snake::SnakeElement Snake::createInitialTail(const sf::Vector2i & position) const
{
	SnakeElement tail;
	tail.type = ElementType::tail;
	tail.direction = Direction::up;
	tail.position = position;

	return tail;
}
