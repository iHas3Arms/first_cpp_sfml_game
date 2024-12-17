#include "Game.h"
#include <iostream>

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
	// this->enemy.setPosition();
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
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
}

void Game::render()
{
	/*
	@ Returns void

	- clear old frame
	- render objects
	- display frame in window
	
	Renders the game objects*/
	this->window->clear();
	this->window->draw(this->enemy);
	this->window->display();
}

bool Game::running()
{
	return this->window->isOpen();
}