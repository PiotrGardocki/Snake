#include "GameOverState.hpp"
#include <Other/Utility.hpp>

GameOverState::GameOverState(StateStack & stateStack, AppState::GlobalContext & context)
	: AppState(stateStack, context),
	mTotalTime(0.f),
	mText("", context.mFonts.get(Fonts::main), 50)
{
	if (context.mGameStatus == GameStatus::gameFailure)
		mText.setString("Game lost");
	else if (context.mGameStatus == GameStatus::gameSuccess)
		mText.setString("Congratulations! You won");

	context.mGameStatus = GameStatus::none;

	centerOrigin(mText);
	mText.setPosition(sf::Vector2f(context.mRenderWindow.getSize()) / 2.f);
}

void GameOverState::draw()
{
	sf::RectangleShape background(sf::Vector2f(mGlobalContext.mRenderWindow.getSize()));
	background.setFillColor(sf::Color(50, 50, 50, 200));

	mGlobalContext.mRenderWindow.draw(background);
	mGlobalContext.mRenderWindow.draw(mText);
}

bool GameOverState::letDrawOtherStates()
{
	return true;
}

bool GameOverState::update(sf::Time deltaTime)
{
	mTotalTime += deltaTime.asSeconds();
	if (mTotalTime >= 4.f)
	{
		requestStateStackClear();
		requestStatePush(State::MenuState);
	}

	return false;
}

bool GameOverState::handleEvent(const sf::Event & event)
{
	return false;
}
