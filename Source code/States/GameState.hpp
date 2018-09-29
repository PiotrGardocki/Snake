#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "AppState.hpp"
#include <GameElements/Board.hpp>

class GameState : public AppState
{
    public:
        GameState(StateStack & stateStack, AppState::GlobalContext & context);
		~GameState();

		virtual void draw() override;
		virtual bool letDrawOtherStates() override;
		virtual bool update(sf::Time deltaTime) override;
		virtual bool handleEvent(const sf::Event & event) override;

    private:
		Board mBoard;
};

#endif // GAMESTATE_HPP_
