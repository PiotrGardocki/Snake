#include "StateStack.hpp"

StateStack::StateStack(AppState::GlobalContext context)
	: mGlobalContext(context)
{
}

void StateStack::update(sf::Time deltaTime)
{
	applyChanges();

	for (int state = mStates.size() - 1; state >= 0; state--)
		if (!mStates[state]->update(deltaTime))
			break;
}

void StateStack::draw()
{
	int state;
	for (state = mStates.size() - 1; state >= 0; --state)
		if (!mStates[state]->letDrawOtherStates())
			break;

	if (state < 0)
		state = 0;

	for (; state < mStates.size(); ++state)
		mStates[state]->draw();
}

void StateStack::handleEvent(const sf::Event & event)
{
	for (int state = mStates.size() - 1; state >= 0; state--)
		if (!mStates[state]->handleEvent(event))
			break;
}

void StateStack::pushState(State::ID stateID)
{
	mChanges.push_back(Change(Push, stateID));
}

void StateStack::popState()
{
	mChanges.push_back(Change(Pop));
}

void StateStack::clearStateStack()
{
	mChanges.push_back(Change(Clear));
}

bool StateStack::isEmpty() const
{
	return mStates.empty();
}

void StateStack::applyChanges()
{
	for (auto & change : mChanges)
	{
		switch (change.mAction)
		{
		case Push:
			mStates.push_back(mStatesFactory.find(change.mStateID)->second());
			break;
		case Pop:
			mStates.pop_back();
			break;
		case Clear:
			mStates.clear();
			break;
		}
	}
	mChanges.clear();
}

StateStack::Change::Change(Action action, State::ID stateID)
	: mAction(action),
	mStateID(stateID)
{
}
