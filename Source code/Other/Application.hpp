#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <SFML/Graphics.hpp>
#include <States/StateStack.hpp>
#include <ResourceStorage/ResourceStorage.hpp>

class Application
{
    public:
        Application();
		void run();

    private:
		void update(sf::Time deltaTime);
		void handleEvents();
		void render();

		void loadTextures();
		void loadFonts();
		void registerStates();

	private:
		sf::RenderWindow mWindow;
		StateStack mStateStack;
		TextureStorage mTextures;
		FontStorage mFonts;
};

#endif // APPLICATION_HPP_
