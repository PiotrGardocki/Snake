#include "Application.hpp"
#include <States/MenuState.hpp>
#include <States/GameState.hpp>
#include <States/PauseState.hpp>
#include <States/GameOverState.hpp>

Application::Application()
	: mWindow(sf::VideoMode(1000, 700), "Snake"),
	mStateStack(AppState::GlobalContext(mWindow, mTextures, mFonts))
{
	mTextures.load(Textures::normalButton, "Images/normal.jpg");
	mTextures.load(Textures::selectButton, "Images/select.jpg");

	mTextures.load(Textures::growBonus, "Images/bonus.png");
	mTextures.load(Textures::snakeHead, "Images/head.png");
	mTextures.load(Textures::snakeBodyStraight, "Images/bodyStraight.png");
	mTextures.load(Textures::snakeBodyTurned, "Images/bodyTurned.png");
	mTextures.load(Textures::snakeTail, "Images/tail.png");

	mFonts.load(Fonts::main, "Sansation.ttf");

	mStateStack.registerState<MenuState>(State::MenuState);
	mStateStack.registerState<GameState>(State::GameState);
	mStateStack.registerState<PauseState>(State::PauseState);
	mStateStack.registerState<GameOverState>(State::GameOverState);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time deltaTime;

	mStateStack.pushState(State::MenuState);

	while (mWindow.isOpen())
	{
		deltaTime += clock.restart();

		handleEvents();

		sf::Time timePerFrame = sf::seconds(1.f / 60.f);
		while (deltaTime > timePerFrame)
		{
			deltaTime -= timePerFrame;
			update(timePerFrame);

			if (mStateStack.isEmpty())
				mWindow.close();
		}

		render();
	}
}

void Application::update(sf::Time deltaTime)
{
	mStateStack.update(deltaTime);
}

void Application::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Application::render()
{
	mWindow.clear();
	mStateStack.draw();
	mWindow.display();
}
