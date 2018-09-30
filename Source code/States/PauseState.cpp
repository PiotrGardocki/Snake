#include "PauseState.hpp"
#include <Other/Utility.hpp>

PauseState::PauseState(StateStack & stateStack, AppState::GlobalContext & context)
	: AppState(stateStack, context),
	mGUIcontainer(mGlobalContext.mRenderWindow)
{
	mGUIcontainer.setMouseControl(true);
	mGUIcontainer.setKeyboardControl(true);

	mGUIcontainer.packComponent(createMenuButton());
	mGUIcontainer.packComponent(createBackToGameButton());

	mView.setCenter(0.f, 0.f);
	onWindowResize();
}

void PauseState::draw()
{
	sf::RenderWindow & window = mGlobalContext.mRenderWindow;

	sf::FloatRect viewRect(getViewRect(mView));

	sf::RectangleShape background(sf::Vector2f(window.getSize()));
	background.setPosition(viewRect.left, viewRect.top);
	background.setFillColor(sf::Color(50, 50, 50, 200));

	window.draw(background);
	window.draw(mGUIcontainer);
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

	if (event.type == sf::Event::Resized)
	{
		onWindowResize();
		return true;
	}
	return false;
}

void PauseState::onWindowResize()
{
	sf::Vector2f windowSize(mGlobalContext.mRenderWindow.getSize());
	mView.setSize(windowSize);
	mGlobalContext.mRenderWindow.setView(mView);
}

std::shared_ptr<Button> PauseState::createMenuButton()
{
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
	menuButton->setPosition(0.f, -50.f);

	return menuButton;
}

std::shared_ptr<Button> PauseState::createBackToGameButton()
{
	std::shared_ptr<Button> backToGame(new Button);
	backToGame->setText("Back to game");
	backToGame->setFont(mGlobalContext.mFonts.get(Fonts::main));
	backToGame->setCharacterSize(20);
	backToGame->setNormalTexture(&(mGlobalContext.mTextures.get(Textures::normalButton)));
	backToGame->setSelectTexture(&(mGlobalContext.mTextures.get(Textures::selectButton)));
	backToGame->setCallback([this]() {
		requestStatePop();
	});
	backToGame->setOrigin(backToGame->getSize() / 2.f);
	backToGame->setPosition(0.f, 50.f);

	return backToGame;
}
