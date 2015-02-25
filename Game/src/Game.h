/**
* \class Game.h
* \brief A class that represents the game field and its interacting
* objects within that field such as asteroids, projectiles and the player in this case.
* \author David Stoddard
* \date February 24, 2015
*/
#pragma once

#include <GameEngine.h>
#include "Player.h"
#include "Projectile.h"
union SDL_Event;
struct SDL_Texture;
struct SDL_Renderer;

class Game : public GameEngine
{
	friend class GameEngine;
public:
	~Game();

protected:
	Game();

	/**
	* \fn void Game::InitializeImpl(SDL_Renderer *renderer)
	* \brief Initialize main game environment and players is drawn to the screen.
	* \param renderer The SDL renderer used to draw the object.
	*/
	void InitializeImpl(SDL_Renderer *renderer);
	/**
	* \fn void Game::InitializeImpl(SDL_Renderer *renderer)
	* \brief Update game to check for inputs,position ,rotation and any actions that have been taken.
	* \param dt keeps count on delta time.
	*/
	void UpdateImpl(float dt);
	/**
	* \fn void Game::DrawImpl(SDL_Renderer *renderer, float dt)
	* \brief Initialize main game environment and players is drawn to the screen.
	* \param renderer The SDL renderer used to draw the object and dt keeps count on delta time.
	*/
	void DrawImpl(SDL_Renderer *renderer, float dt);
	/**
	* \fn void Game::RenderWorldWalls(SDL_Renderer *renderer, SDL_Rect *wall1, SDL_Rect *wall2)
	* \brief Renders rectangle walls.
	* \param renderer The SDL renderer used to draw the walls, SDL_Rects are passed to render them.
	*/
	void RenderWorldWalls(SDL_Renderer *renderer, SDL_Rect *wall1, SDL_Rect *wall2);
	/**
	* \fn void Game::Collision()
	* \brief Collision detection logic for players and walls.
	* \param n/a
	*/
	void Collision();
	/**
	* \fn void Game::GetPlayerProjectilePos(Player *player, float x1, float x2, float y1, float y2)
	* \brief Get player projectile position.
	* \param Player object pointer and line of projectile are passed to check current projectile position.
	*/
	void GetPlayerProjectilePos(Player *player, float x1, float x2, float y1, float y2);

	Player _player1;
	Player _player2;
	Vector3 _player1Pos;
	Vector3 _player2Pos;
	Vector3 _projectilePos;
	Vector2 _endPointOffset;
	Vector2 _player1DirectionVec;
	Vector2 _player2DirectionVec;
	SDL_Rect _wall1, _wall2;
	float x1, x2, y1, y2;
	float _speed;
	float _rotSpeed;
	float _player1Radians;
	float _player2Radians;
	int _player1Score;
	int _player2Score;
	char _score[200];
};