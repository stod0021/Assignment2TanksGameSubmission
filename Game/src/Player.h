/**
* \class Player.h
* \brief A player class that represents the player
* that can move a tank, fire projectiles and die from enemy tanks.
* \author David Stoddard
* \date February 24, 2015
*/
#pragma once

#include "GameObject.h"
#include <SDL.h>
#include "Projectile.h"
struct SDL_Surface;
struct SDL_Window;
struct SDL_Texture;

class Player : public GameObject
{
public:
	Player();
	~Player();
	//Projectile is public to player
	Projectile projectile;

	void Initialize(SDL_Renderer * renderer, const char *fileName);

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);

	void SetPosition(Vector3 pos);
	/**
	* \fn Vector3 Player::GetPosition()
	* \brief A function that is used to get the player sposition.
	* \return Vector3 The position fo the player.
	*/
	Vector3 GetPosition();
	/**
	* \fn void Player::SetPlayerSpeed(int speed)
	* \brief A function that is used to set the speed of the player
	* \param speed The speed to set the player to.
	*/
	void SetPlayerSpeed(float speed);
	/**
	* \fn int Player::GetPlayerSpeed()
	* \brief A function that is used to set the speed of the player
	* \return int The speed the player is traveling at.
	*/
	float GetPlayerSpeed();
	/**
	* \fn Vector3 Player::GetDirectionVector()
	* \brief A function that is used to get the direction of the player
	* \return Vector3 The direction the player is traveling
	*/
	Vector2 GetDirectionVector();
	/**
	* \fn void Player::SetDirectionVector(Vector3 direction)
	* \brief A function that is used to set the direction the player is traveling
	* \param Vector3 The travel direction to set the player to
	*/
	void SetDirectionVector(Vector2 direction);
	/**
	* \fn Vector3 Player::GetPlayerRotation()
	* \brief Get the current player rotation
	* \return Float rotation of the player.
	*/
	float GetPlayerRotation();
	/**
	* \fn void Player::SetPlayerRotation(float endPoint)
	* \brief Sets the player rotation 
	* \param Float endPoint 
	*/
	void SetPlayerRotation(float endPoint);
	/**
	* \fn void Player::SetPlayerRotation(float speed)
	* \brief Sets the player rotation speed.
	* \param Float speed is the speed of rotation.
	*/
	void SetPlayerRotationSpeed(float speed);
	/**
	* \fn void Player::SetTankIsDead(bool isDead)
	* \brief Sets the deathstate of the tank.
	* \param Bool isDead sets tank is dead or not.
	*/
	void SetTankIsDead(bool isDead);
	/**
	* \fn bool Player::GetTankIsDead()
	* \brief Checks if player is dead
	* \return boolean
	*/
	bool GetTankIsDead();
	/**
	* \fn float Player::GetPlayerRotationSpeed()
	* \brief Gets the current player rotation speed.
	* \return float
	*/
	float GetPlayerRotationSpeed();
	/**
	* \fn SDL_Rect Player::GetTankRect()
	* \brief Get tank rect structure. Height,width and position.
	* \return SDL_Rect
	*/
	SDL_Rect GetTankRect();
	/**
	* \fn void Player::SetTankDeadTime(float time)
	* \brief Sets tank time to be dead.
	* \param Float time is the duration of the tanks death.
	*/
	void SetTankDeadTime(float time);

protected:

	float _tankRotationSpeed;
	float _tankAngle;
	float _timeDead;
	float _tankSpeed;
	bool _tankIsDead = false;
	Vector2 _tankRotationOffSet;
	SDL_Point _centre;
	Vector2 _tankDirectionVector;
	Vector3 _tankPos;
	SDL_Rect _tankRect;
	SDL_Texture *_tankTexture;
};