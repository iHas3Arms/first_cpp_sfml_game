#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	
	this->window = new sf::RenderWindow(this->videoMode, "SKIBIDI TOILET!", sf::Style::Default);

	this->window->setFramerateLimit(60);
}

// Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color(255, 255, 0, 255));
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}

Game::~Game()
{
	delete this->window;
}

// Functions
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	// Update mouse position
	//   Relative to the screen
	//std::cout << "__Mouse position relative to screen__\n"
	//		  << "x: " << sf::Mouse::getPosition().x
	//		  << "\ny: " << sf::Mouse::getPosition().y;

	//   Relative to window
	std::cout << "mouse pos | x: " << sf::Mouse::getPosition(*this->window).x 
		      << " y: " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void Game::render()
{
	/*
		@ Returns void

		- clear old frame
		- render objects
		- display frame in window
	
		Renders the game objects
	*/
	this->window->clear();
	this->window->draw(this->enemy);
	this->window->display();
}

bool Game::running()
{
	return this->window->isOpen();
}