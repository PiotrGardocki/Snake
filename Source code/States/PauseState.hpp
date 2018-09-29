#ifndef PAUSESTATE_HPP_
#define PAUSESTATE_HPP_

#include "AppState.hpp"
#include <GUI/GUIContainer.hpp>

class PauseState : public AppState
{
    public:
        PauseState(StateStack & stateStack, AppState::GlobalContext & context);

		virtual void draw() override;
		virtual bool letDrawOtherStates() override;
		virtual bool update(sf::Time deltaTime) override;
		virtual bool handleEvent(const sf::Event & event) override;

	private:
		GUIContainer mGUIcontainer;
};

#endif // PAUSESTATE_HPP_
