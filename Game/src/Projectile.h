/**
* \class Projectile.h
* \brief A projectile class that represents the projectile
* that is fired from the players location,direction and bounces off walls until destroyed(by player hit or after 3 bounces).
* \author David Stoddard
* \date February 24, 2015
*/
#pragma once
#include "GameObject.h"
#include <SDL.h>

struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	/**
	* \fn void Projectile::Initialize(SDL_Renderer * renderer, const char *fileName)
	* \brief Initializes projectile for player 1 or 2.
	* \param SDL_Renderer is used to draw the projetile, while the fileName is the path to the bitmap applied to the texture.
	*/
	void Initialize(SDL_Renderer * renderer, const char *fileName);
	/**
	* \fn void Projectile::Update(float dt)
	* \brief Checks if projectile is alive and updates the projectile accordingly
	* \param Float delta time keeps track of time passed.
	*/
	void Update(float dt);
	/**
	* \fn void Projectile::Draw(SDL_Renderer *renderer, float dt)
	* \brief Draws the projectile
	* \param SDL_Renderer is used to draw the projetile, float is delta time.
	*/
	void Draw(SDL_Renderer *renderer, float dt);
	/**
	* \fn void Projectile::SetPosition(Vector3 position)
	* \brief Set the current position of projectile
	* \param Vector3 position applied.
	*/
	void SetPosition(Vector3 position);
	/**
	* \fn Vector3 Projectile::GetPosition()
	* \brief Gets the current position of projectile
	* \param n/a
	*/
	Vector3 GetPosition();
	/**
	* \fn void Projectile::SetProjectileIsLive(SDL_Renderer *renderer, float dt)
	* \brief Draws the projectile
	* \param SDL_Renderer is used to draw the projetile, float is delta time.
	*/
	void SetProjectileIsLive(bool isLive);
	/**
	* \fn bool Projectile::GetProjectileIsLive()
	* \brief Check if projectile is alive.
	* \param n/a
	*/
	bool GetProjectileIsLive();
	/**
	* \fn void Projectile::SetProjectileLife(int life)
	* \brief Sets projectile life is set.
	* \param Int life is applied.
	*/
	void SetProjectileLife(int life);
	/**
	* \fn int Projectile::GetProjectileLife(SDL_Renderer *renderer, float dt)
	* \brief Gets the remaining life of the projectile
	* \param n/a
	*/
	int GetProjectileLife();
	/**
	* \fn void Projectile::SetProjectileIsFired(bool isFired)
	* \brief Sets projectile isFired or not fired.
	* \param Bool isFired applies true or false. 
	*/
	void SetProjectileIsFired(bool isFired);
	/**
	* \fn bool Projectile::GetProjectileIsFired()
	* \brief Check if projectile is fired.
	* \param n/a
	*/
	bool GetProjectileIsFired();
	/**
	* \fn void Projectile::SetRotation(float rotation)
	* \brief Set rotation of the projectile
	* \param Float rotation applied.
	*/
	void SetRotation(float rotation);
	/**
	* \fn Vector3 Projectile::GetRotation()
	* \brief Get rotation of projectile
	* \param n/a
	*/
	Vector3 GetRotation();
	/**
	* \fn void Projectile::SetProjectileOffSet(Vector2 offset)
	* \brief Set projectile offset
	* \param Vector2 offset being applied.
	*/
	void SetProjectileOffSet(Vector2 offset);
	/**
	* \fn Vector2 Projectile::GetProjectileOffset()
	* \brief Gets the projectile offset.
	* \param n/a
	*/
	Vector2 GetProjectileOffset();
	/**
	* \fn Vector2 Projectile::GetProjectilePos()
	* \brief Gets the projectile position
	* \param n/a
	*/
	Vector2 GetProjectilePos();


protected:
	Vector2 _projectilePosition;
	Vector2 _projectileOffSet;
	SDL_Texture *_projectileTexture;
	SDL_Rect _projectileStructure;
	SDL_Point _centre;
	int _projectileLife;
	bool _projectileFired = false;
	bool _projectileLive = false;
};