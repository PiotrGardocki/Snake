#include "GameState.hpp"

GameState::GameState(StateStack & stateStack, AppState::GlobalContext & context)
	: AppState(stateStack, context),
	mBoard(sf::Vector2u(10, 10), 30.f, context.mTextures, context.mGameStatus),
	mView(sf::Vector2f(0.f, 0.f), sf::Vector2f(mGlobalContext.mRenderWindow.getSize()))
{
	context.mGameStatus = GameStatus::gameRunning;

	sf::Vector2f boardSize = mBoard.getBoardSize();
	mBoard.setOrigin(boardSize / 2.f);
}

GameState::~GameState()
{
	mGlobalContext.mGameStatus = GameStatus::none;
}

void GameState::draw()
{
	sf::RenderWindow & window = mGlobalContext.mRenderWindow;
	const sf::View oldView = window.getView();

	window.setView(mView);
	window.draw(mBoard);

	window.setView(oldView);
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
	if (event.type == sf::Event::Resized)
		mView.setSize(sf::Vector2f(mGlobalContext.mRenderWindow.getSize()));

	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStatePush(State::PauseState);
	else
		mBoard.handleEvent(event);
	return false;
}
