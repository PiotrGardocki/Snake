#ifndef STATESTACK_HPP_
#define STATESTACK_HPP_

#include <map>
#include <functional>
#include <memory>
#include <vector>
#include "AppState.hpp"

class StateStack
{
    public:
		explicit StateStack(AppState::GlobalContext context);

		void update(sf::Time deltaTime);
		void draw();
		void handleEvent(const sf::Event & event);

		void pushState(State::ID stateID);
		void popState();
		void clearStateStack();

		bool isEmpty() const;

		template <typename T>
		void registerState(State::ID stateID);

	private:
		void applyChanges();

    private:
		enum Action
		{
			Push,
			Pop,
			Clear
		};

		struct Change
		{
			explicit Change(Action action, State::ID stateID = State::None);

			Action mAction;
			State::ID mStateID;
		};

		std::vector<std::unique_ptr<AppState>> mStates;
		AppState::GlobalContext mGlobalContext;
		std::vector<Change> mChanges;

		std::map<State::ID, std::function<std::unique_ptr<AppState>()>> mStatesFactory;
};

template <typename T>
void StateStack::registerState(State::ID stateID)
{
	mStatesFactory[stateID] = [this]()
	{
		return std::unique_ptr<AppState>(new T(*this, mGlobalContext));
	};
}

#endif // STATESTACK_HPP_
