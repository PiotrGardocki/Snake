#include "PauseState.hpp"
#include <GUI/Button.hpp>

PauseState::PauseState(StateStack & stateStack, AppState::GlobalContext & context)
	: AppState(stateStack, context),
	mGUIcontainer(mGlobalContext.mRenderWindow)
{
	mGUIcontainer.setMouseControl(true);

	std::shared_ptr<Button> menuButton(new Button);
	menuButton->setText("Exit");
	menuButton->setFont(mGlobalContext.mFonts.get(Fonts::main));
	menuButton->setCharacterSize(20);
	menuButton->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	menuButton->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	menuButton->setCallback([this]() {
		requestStateStackClear();
		requestStatePush(State::MenuState);
	});
	menuButton->setOrigin(menuButton->getSize() / 2.f);
	menuButton->setPosition(mGlobalContext.mRenderWindow.getSize().x / 2.f, 200.f);

	std::shared_ptr<Button> backToGame(new Button);
	backToGame->setText("Back to game");
	backToGame->setFont(mGlobalContext.mFonts.get(Fonts::main));
	backToGame->setCharacterSize(20);
	backToGame->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	backToGame->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	backToGame->setCallback([this]() {
		requestStatePop();
	});
	backToGame->setOrigin(menuButton->getSize() / 2.f);
	backToGame->setPosition(mGlobalContext.mRenderWindow.getSize().x / 2.f, 300.f);

	mGUIcontainer.packComponent(menuButton);
	mGUIcontainer.packComponent(backToGame);
}

void PauseState::draw()
{
	sf::RectangleShape background(sf::Vector2f(mGlobalContext.mRenderWindow.getSize()));
	background.setFillColor(sf::Color(50, 50, 50, 200));

	mGlobalContext.mRenderWindow.draw(background);
	mGlobalContext.mRenderWindow.draw(mGUIcontainer);
}

bool PauseState::letDrawOtherStates()
{
	return true;
}

bool PauseState::update(sf::Time deltaTime)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event & event)
{
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		requestStatePop();
	else
		mGUIcontainer.handleEvent(event);

	return false;
}
