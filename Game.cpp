#include "Game.h"

// Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	// Assign values
	this->health = 10;
	this->points = 0;
	this->endGame = false;
	this->enemySpawnTimer = 0.f;
	this->enemySpawnTimerMax = 500.f;
	// Changes values of enemySpeed
	this->enemySpeed = { 1.f, 5.f };
	this->maxEnemies = 8;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	
	this->window = new sf::RenderWindow(this->videoMode, "SKIBIDI TOILET!", sf::Style::Default);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	std::string fontPath = "graphics/Poppins-Medium.ttf";
	if (this->font.loadFromFile(fontPath))
	{
		std::cout << "ERROR::GAME::INITFONTS::Failed to load fonts" << std::endl;
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(12);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Blue);
	this->uiText.setOutlineThickness(1.f);
	this->uiText.setString("NONE");
}

// Constructors / Destructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initEnemies();
}

void Game::initEnemies()
{
	this->enemy.setPosition(sf::Vector2f(10.f, 10.f));
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color(255, 255, 0, 255));
	// this->enemy.setOutlineColor(sf::Color::Green);
	// this->enemy.setOutlineThickness(1.f);
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

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	// std::cout << mousePosView.x << "  " << mousePosView.y << std::endl;
}

void Game::spawnEnemy()
{
	/*
	@ return void
	
	Spawns enemies and sets their types and colours. Sets positions randomly.
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

	// Randomise enemy type
	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->enemy.setFillColor(sf::Color::Magenta);
		this->enemy.setSize(sf::Vector2f(10.f, 10.f));
		break;
	case 1:
		this->enemy.setFillColor(sf::Color::Red);
		this->enemy.setSize(sf::Vector2f(30.f, 30.f));
		break;
	case 2:
		this->enemy.setFillColor(sf::Color::Yellow);
		this->enemy.setSize(sf::Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(sf::Color::Cyan);
		this->enemy.setSize(sf::Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy.setFillColor(sf::Color::Green);
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		break;
	default:
		this->enemy.setFillColor(sf::Color::Blue);
		this->enemy.setSize(sf::Vector2f(200.f, 200.f));
		break;
	}

	std::cout << this->enemy.getPosition().x << "  " << enemy.getPosition().y << std::endl;

	// Adds new enemy ('spawns' it in)
	this->enemies.push_back(enemy);

	std::cout << "No. of enemies: " << this->enemies.size() << std::endl;
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\nHealth: " << this->health;

	this->uiText.setString(ss.str());
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

	// Move and updating enemies
	for (int i = 0; i < this->enemies.size(); i++) // auto &e : this->enemies
	{
		this->enemies[i].move(this->enemySpeed.x, this->enemySpeed.y); // e.move(...);

		// If the enemy is past the bottom of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			// that enemy will be despawned (removed from enemies vector)
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}

	}

	// Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					// Gain points
					if (this->enemies[i].getFillColor() == sf::Color::Magenta)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 4;
					else if (this->enemies[i].getFillColor() == sf::Color::Yellow)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 2;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;

					// Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					std::cout << "Points: " << this->points << std::endl;
				}
			}
		}
		// Nothing here
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderText()
{
	this->window->draw(this->uiText);
}

void Game::renderEnemies()
{
	// Rendering all the enemies
	for (auto &e : this->enemies)
	{
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

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	this->updateEnemies();

	// Endgame Condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}
	this->updateText();
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
	this->renderText();

	this->window->display();
}

bool Game::running()
{
	return this->window->isOpen() && !this->getEndGame();
}