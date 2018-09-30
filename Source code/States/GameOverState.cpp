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

	mView.setCenter(0.f, 0.f);
	onWindowResize();
}

void GameOverState::draw()
{
	sf::RenderWindow & window = mGlobalContext.mRenderWindow;

	sf::FloatRect viewRect(getViewRect(mView));

	sf::RectangleShape background(sf::Vector2f(window.getSize()));
	background.setPosition(viewRect.left, viewRect.top);
	background.setFillColor(sf::Color(50, 50, 50, 200));

	window.draw(background);
	window.draw(mText);
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
	if (event.type == sf::Event::Resized)
	{
		onWindowResize();
		return true;
	}
	return false;
}

void GameOverState::onWindowResize()
{
	sf::Vector2f windowSize(mGlobalContext.mRenderWindow.getSize());
	mView.setSize(windowSize);
	mGlobalContext.mRenderWindow.setView(mView);
}
