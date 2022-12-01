#include "..\DuxsonEngine\include\SFMLWindow.h"
#include "..\DuxsonEngine\include\SFMLInput.h"
#include <iostream>

using namespace DE;

int main()
{
	SFMLInput::SPtr input = std::make_shared<SFMLInput>();
	SFMLWindow::SPtr window = std::make_shared<SFMLWindow>(input);

	while (window->isOpen())
	{
		window->update();
		window->swapBuffers();

		//Test input
		if (input->isMouseBtnPressed(sf::Mouse::Left))
			std::cout << "Left Mouse button pressed\n";
		if (input->isKeyPressed(sf::Keyboard::A))
			std::cout << "A keboard key pressed\n";

		//Closing of window via a key press
		if (input->isKeyPressed(sf::Keyboard::Escape))
			window->closeWindow();
	}

	return 0;
}