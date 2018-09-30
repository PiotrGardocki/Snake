#ifndef PAUSESTATE_HPP_
#define PAUSESTATE_HPP_

#include "AppState.hpp"
#include <GUI/GUIContainer.hpp>
#include <GUI/Button.hpp>

class PauseState : public AppState
{
    public:
        PauseState(StateStack & stateStack, AppState::GlobalContext & context);

		virtual void draw() override;
		virtual bool letDrawOtherStates() override;
		virtual bool update(sf::Time deltaTime) override;
		virtual bool handleEvent(const sf::Event & event) override;

	private:
		void onWindowResize();

		std::shared_ptr<Button> createMenuButton();
		std::shared_ptr<Button> createBackToGameButton();

	private:
		GUIContainer mGUIcontainer;
		sf::View mView;
};

#endif // PAUSESTATE_HPP_
