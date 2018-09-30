#ifndef GAMEOVERSTATE_HPP_
#define GAMEOVERSTATE_HPP_

#include "AppState.hpp"

class GameOverState : public AppState
{
    public:
        GameOverState(StateStack & stateStack, AppState::GlobalContext & context);

		virtual void draw() override;
		virtual bool letDrawOtherStates() override;
		virtual bool update(sf::Time deltaTime) override;
		virtual bool handleEvent(const sf::Event & event) override;

	private:
		void onWindowResize();

    private:
		float mTotalTime;
		sf::Text mText;
		sf::View mView;
};

#endif // GAMEOVERSTATE_HPP_
