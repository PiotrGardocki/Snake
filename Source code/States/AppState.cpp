#include "AppState.hpp"
#include "StateStack.hpp"

AppState::AppState(StateStack & stateStack, GlobalContext & context)
	: mStateStack(stateStack), mGlobalContext(context)
{
}

AppState::~AppState()
{
}

void AppState::requestStatePush(State::ID stateID)
{
	mStateStack.pushState(stateID);
}

void AppState::requestStatePop()
{
	mStateStack.popState();
}

void AppState::requestStateStackClear()
{
	mStateStack.clearStateStack();
}

AppState::GlobalContext::GlobalContext(sf::RenderWindow & renderWindow, TextureStorage & textures, FontStorage & fonts)
	: mRenderWindow(renderWindow),
	mTextures(textures),
	mFonts(fonts),
	mGameStatus(GameStatus::none)
{
}
