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
	unsigned points;
	int health;
	bool endGame;

	bool mouseHeld;

	// ^ Enemies
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	// Creates the struct Speed, now as a data type, which takes the int values x, and y
	struct Speed { float x; float y; };
	// Declares an instance of the Speed struct by creating variable speed
	Speed enemySpeed = { 0.f, 0.f };
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
	const bool getEndGame() const;

	// Functions
	void spawnEnemy();

	void pollEvents();
	void updateMousePositions();
	void updateEnemies();
	void update();
	void renderEnemies();
	void render();
};