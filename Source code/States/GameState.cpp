#include "GameState.hpp"

GameState::GameState(StateStack & stateStack, AppState::GlobalContext & context)
	: AppState(stateStack, context),
	mBoard(sf::Vector2u(10, 10), 30.f, context.mTextures, context.mGameStatus)
{
	context.mGameStatus = GameStatus::gameRunning;

	sf::Vector2f boardSize = mBoard.getBoardSize();
	mBoard.setOrigin(boardSize / 2.f);
	mBoard.setPosition(sf::Vector2f(mGlobalContext.mRenderWindow.getSize()) / 2.f);
}

GameState::~GameState()
{
	mGlobalContext.mGameStatus = GameStatus::none;
}

void GameState::draw()
{
	mGlobalContext.mRenderWindow.draw(mBoard);
}

bool GameState::letDrawOtherStates()
{
	return false;
}

bool GameState::update(sf::Time deltaTime)
{
	mBoard.update(deltaTime);
	if (mGlobalContext.mGameStatus != GameStatus::gameRunning)
		requestStatePush(State::GameOverState);
	return false;
}

bool GameState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStatePush(State::PauseState);
	else
		mBoard.handleEvent(event);
	return false;
}
