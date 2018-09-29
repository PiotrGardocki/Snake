#ifndef APPSTATE_HPP_
#define APPSTATE_HPP_

#include <SFML/Graphics.hpp>
#include "StatesIdentifiers.hpp"
#include <ResourceStorage/ResourceStorage.hpp>
#include <GameElements/GameStatus.hpp>

class StateStack;

class AppState
{
    public:
		struct GlobalContext
		{
			GlobalContext(sf::RenderWindow & renderWindow, TextureStorage & textures, FontStorage & fonts);

			sf::RenderWindow & mRenderWindow;
			TextureStorage & mTextures;
			FontStorage & mFonts;
			GameStatus mGameStatus;
		};

        AppState(StateStack & stateStack, GlobalContext & context);
		virtual ~AppState();

		virtual void draw() = 0;
		virtual bool letDrawOtherStates() = 0;
		virtual bool update(sf::Time deltaTime) = 0;
		virtual bool handleEvent(const sf::Event & event) = 0;

	protected:
		void requestStatePush(State::ID stateID);
		void requestStatePop();
		void requestStateStackClear();

		GlobalContext & mGlobalContext;

    private:
		StateStack & mStateStack;
};

#endif // APPSTATE_HPP_
