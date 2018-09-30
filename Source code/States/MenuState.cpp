#include "MenuState.hpp"
#include <GUI/Button.hpp>

MenuState::MenuState(StateStack & stateStack, GlobalContext & context)
	: AppState(stateStack, context),
	mGUIcontainer(context.mRenderWindow)
{

	mGUIcontainer.setMouseControl(true);
	mGUIcontainer.setKeyboardControl(true);
	
	mGUIcontainer.packComponent(createPlayButton());
	mGUIcontainer.packComponent(createExitButton());

	onWindowResize();
}

void MenuState::draw()
{
	// background

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

	if (event.type == sf::Event::Resized)
	{
		onWindowResize();
		return true;
	}
	return false;
}

void MenuState::onWindowResize()
{
	sf::Vector2f windowSize(mGlobalContext.mRenderWindow.getSize());
	sf::FloatRect viewRect(sf::Vector2f(0.f, 0.f), windowSize);
	mView.reset(viewRect);
	mGlobalContext.mRenderWindow.setView(mView);
}

std::shared_ptr<Button> MenuState::createPlayButton()
{
	std::shared_ptr<Button> playButton(new Button);
	playButton->setText("Play");
	playButton->setFont(mGlobalContext.mFonts.get(Fonts::main));
	playButton->setCharacterSize(30);
	playButton->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	playButton->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	playButton->setCallback([this]() {
		requestStatePop();
		requestStatePush(State::GameState);
	});
	playButton->setPosition(100.f, 150.f);

	return playButton;
}

std::shared_ptr<Button> MenuState::createExitButton()
{
	std::shared_ptr<Button> exitButton(new Button);
	exitButton->setText("Exit");
	exitButton->setFont(mGlobalContext.mFonts.get(Fonts::main));
	exitButton->setCharacterSize(30);
	exitButton->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	exitButton->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	exitButton->setCallback([this]() {
		requestStateStackClear();
	});
	exitButton->setPosition(100.f, 250.f);

	return exitButton;
}
