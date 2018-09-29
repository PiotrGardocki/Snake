#include <iostream>

#include "Application.hpp"

#include <fstream>
#include <GameElements/Board.hpp>

int main()
{
	std::srand(std::time(0));

	Application app;
	app.run();

	using std::cout;
	using std::endl;

	/*sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	TextureStorage textures;
	textures.load(Textures::normalButton, "normal.jpg");
	textures.load(Textures::selectButton, "select.jpg");
	textures.load(Textures::activeButton, "active.jpg");

	FontStorage fonts;
	fonts.load(Fonts::main, "Sansation.ttf");
	
	GUIContainer container(window);

	std::shared_ptr<Button> button1(new Button);
	button1->setFont(fonts.get(Fonts::main));
	button1->setText("Zagraj");
	button1->setCharacterSize(30);
	button1->setNormalTexture(&textures.get(Textures::normalButton));
	button1->setSelectTexture(&textures.get(Textures::selectButton));
	button1->setPosition(10, 10);
	button1->setSelectable(true);

	std::shared_ptr<Button> button2(new Button);
	button2->setFont(fonts.get(Fonts::main));
	button2->setText("Opcje");
	button2->setCharacterSize(30);
	button2->setNormalTexture(&textures.get(Textures::normalButton));
	button2->setSelectTexture(&textures.get(Textures::selectButton));
	button2->setPosition(200, 10);
	button2->setSelectable(true);

	std::shared_ptr<Button> button3(new Button);
	button3->setFont(fonts.get(Fonts::main));
	button3->setText("Zamknij");
	button3->setCharacterSize(30);
	button3->setNormalTexture(&textures.get(Textures::normalButton));
	button3->setSelectTexture(&textures.get(Textures::selectButton));
	button3->setPosition(390, 10);
	button3->setSelectable(true);

	container.packComponent(button1);
	container.packComponent(button2);
	container.packComponent(button3);

	container.setMouseControl(true);
	container.setKeyboardControl(true);*/




	/*sf::RenderWindow window(sf::VideoMode(1000, 600), "SFML works!");
	TextureStorage textures;
	textures.load(Textures::snakeHead, "Images/head.png");
	textures.load(Textures::snakeBodyStraight, "Images/bodyStraight.png");
	textures.load(Textures::snakeBodyTurned, "Images/bodyTurned.png");
	textures.load(Textures::snakeTail, "Images/tail.png");
	textures.load(Textures::growBonus, "Images/bonus.png");

	GameStatus mGameStatus = GameStatus::gameRunning;
	Board board(sf::Vector2u(6, 6), 30.f, textures, mGameStatus);
	sf::Clock clock;

	board.setPosition(500, 300);
	board.setOrigin(90, 90);
	//board.rotate(-5);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			board.handleEvent(event);
		}
		
		if (mGameStatus == GameStatus::gameRunning)
			board.update(clock.restart());

		if (mGameStatus == GameStatus::gameSuccess)
			cout << "X";

		window.clear();

		window.draw(board);

		window.display();
	}*/

    return 0;
}
