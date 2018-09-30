#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include "AppState.hpp"
#include <GUI/Button.hpp>
#include <GUI/GUIContainer.hpp>

class MenuState : public AppState
{
    public:
        MenuState(StateStack & stateStack, GlobalContext & context);

		virtual void draw() override;
		virtual bool letDrawOtherStates() override;
		virtual bool update(sf::Time deltaTime) override;
		virtual bool handleEvent(const sf::Event & event) override;

	private:
		void onWindowResize();

		std::shared_ptr<Button> createPlayButton();
		std::shared_ptr<Button> createExitButton();

    private:
		GUIContainer mGUIcontainer;
		sf::View mView;
};

#endif // MENUSTATE_HPP_
