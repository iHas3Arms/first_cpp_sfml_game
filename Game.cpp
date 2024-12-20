#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	// Assign values
	this->points = 0;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 1000.f;
	this->maxEnemies = 5;
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

void Game::updateMousePositions()
{
	/*
	@ returns void

	Updates the mouse positions:
		- Mouse position relative to window (and Vector2i, not Vector2f)
	*/

	std::cout << "mouse pos | x: " << sf::Mouse::getPosition(*this->window).x
			  << " y: " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void Game::spawnEnemy()
{
	/*
	@ return void
	
	Spawns enemies and sets their colours and positions
	- Sets a random position
	- Sets a random colour
	0 Adds enemy to the vector
	*/
	
	// static_cast<> used to implicitly convert from float to int and int to float
	this->enemy.setPosition(
		static_cast<float>(
			rand() % static_cast<int>(this->videoMode.width - this->enemy.getSize().x)
		),
		static_cast<float>(
			rand() % static_cast<int>(this->videoMode.height - this->enemy.getSize().y)
		)
	);

	std::cout << this->enemy.getPosition().x << "  " << enemy.getPosition().y << std::endl;

	this->enemy.setFillColor(sf::Color::Green);

	// Adds new enemy ('spawns' it in)
	this->enemies.push_back(enemy);

}

void Game::updateEnemies()
{
	/*
	@ return void
	
	update the enemy spawn timer and spawns enemies when the total
	amount of enemies is smaller than the max amount.
	Removes enemies at the edge of the screen **TODO**
	*/

	// Init seed for rand()
	srand(static_cast<unsigned>(time(NULL)));

	// Updating timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1 + static_cast<float>(rand() % 10);
		}
	}

	// Move the enemies
	for (auto &e : this->enemies)
	{
		e.move(0.f, 0.5f);
	}
}

void Game::renderEnemies()
{
	// Rendering all the enemies
	for (auto &e : this->enemies) {
		this->window->draw(e);
	}
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

	// this->updateMousePositions();

	this->updateEnemies();
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
	this->renderEnemies();

	// render UI last so not blocked by any other objects

	this->window->display();
}

bool Game::running()
{
	return this->window->isOpen();
}