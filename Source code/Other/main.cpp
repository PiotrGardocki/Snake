#include <iostream>

#include "Application.hpp"

#include <fstream>
#include <GameElements/Board.hpp>

#include <stdexcept>

int main()
{
	try
	{
		Application app;
		app.run();
	}
	catch (const std::exception & except)
	{
		std::cout << "Thrown exception, what(): " << except.what();
		std::cin.get();
	}

    return 0;
}
