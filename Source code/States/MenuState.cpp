#include "MenuState.hpp"

MenuState::MenuState(StateStack & stateStack, GlobalContext & context)
	: AppState(stateStack, context),
	mGUIcontainer(context.mRenderWindow)
{

	mGUIcontainer.setMouseControl(true);
	mGUIcontainer.setKeyboardControl(true);

	const sf::Font & font(context.mFonts.get(Fonts::main));

	std::shared_ptr<Button> playButton(new Button);
	playButton->setText("Play");
	playButton->setFont(font);
	playButton->setCharacterSize(30);
	playButton->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	playButton->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	playButton->setCallback([this]() {
		requestStatePop();
		requestStatePush(State::GameState);
	});
	playButton->setPosition(100.f, 150.f);

	std::shared_ptr<Button> exitButton(new Button);
	exitButton->setText("Exit");
	exitButton->setFont(font);
	exitButton->setCharacterSize(30);
	exitButton->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	exitButton->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	exitButton->setCallback([this]() {
		requestStateStackClear();
	});
	exitButton->setPosition(100.f, 250.f);

	mGUIcontainer.packComponent(playButton);
	mGUIcontainer.packComponent(exitButton);
}

void MenuState::draw()
{
	// tlo

	mGlobalContext.mRenderWindow.draw(mGUIcontainer);
}

bool MenuState::letDrawOtherStates()
{
	return false;
}

bool MenuState::update(sf::Time deltaTime)
{
	return false;
}

bool MenuState::handleEvent(const sf::Event & event)
{
	mGUIcontainer.handleEvent(event);

	return false;
}
