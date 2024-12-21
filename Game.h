#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/
class Game
{
private:
	// Variables

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Game logic variables
	int points;

	// ^ Enemies
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;

	// Game objects
	// > Enemies
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private functions
	void initVariables();
	void initWindow();
	void initEnemies();

public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Accessors
	bool running();

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};