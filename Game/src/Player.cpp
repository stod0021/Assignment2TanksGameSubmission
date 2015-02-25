#include "Player.h"
#include <math.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

Player::Player() : GameObject()
{
}

Player::~Player()
{
	SDL_DestroyTexture(_tankTexture);
}

void Player::Initialize(SDL_Renderer * renderer, const char *fileName)
{
	_tankTexture = IMG_LoadTexture(renderer, fileName);
	if (_tankTexture == NULL){
		printf(SDL_GetError());
	}

	_tankSpeed = 50.0f;
	_tankRect.h = 30;
	_tankRect.w = 50;
}

void Player::Update(float dt)
{
	_tankPos.x = _transform.position.x;
	_tankPos.y = _transform.position.y;

	_tankAngle += (_tankAngle >= 360.0f ? -360.0f : 0);

	if (_tankIsDead == true)
	{
		_timeDead -= dt;
		_tankAngle += 720 * dt;
	}
	if (_timeDead < 0 )
	{
		_tankIsDead = false;
	}
	_tankAngle = MathUtils::ToDegrees(_tankAngle);

}

void Player::Draw(SDL_Renderer *renderer, float dt)
{ 

	_centre = { _tankRect.w / 2 , _tankRect.h / 2 };
	_tankRect.x = (_tankPos.x - _centre.x);
	_tankRect.y = (_tankPos.y - _centre.y);

	//_tankRotationOffSet = { 10.0 * sinf(MathUtils::ToRadians(_tankAngle)), -10.0 * cosf(MathUtils::ToRadians(_tankAngle)) };
	SDL_RenderCopyEx(renderer, _tankTexture, NULL, &_tankRect, _tankAngle, &_centre, SDL_FLIP_NONE);
}
/*Get methods*/

void Player::SetPosition(Vector3 position)
{
	_transform.position = position;
}

Vector3 Player::GetPosition()
{
	return this->_transform.position;
}

void Player::SetPlayerSpeed(float speed)
{
	_tankSpeed = speed;
}

float Player::GetPlayerSpeed()
{
	return _tankSpeed;
}

void Player::SetDirectionVector(Vector2 directionVector)
{
	_tankDirectionVector = directionVector;
}

Vector2 Player::GetDirectionVector()
{
	return _tankDirectionVector;
}

float Player::GetPlayerRotation()
{
	return _tankAngle;
}

void Player::SetPlayerRotation(float degrees)
{
	_tankAngle = degrees;
}


void Player::SetPlayerRotationSpeed(float speed)
{
	_tankRotationSpeed = speed;
}

float Player::GetPlayerRotationSpeed()
{
	return _tankRotationSpeed;
}

SDL_Rect Player::GetTankRect()
{
	return _tankRect;
}

void Player::SetTankIsDead(bool isDead)
{
	_tankIsDead = isDead;
}

bool Player::GetTankIsDead()
{
	return _tankIsDead;
}


void Player::SetTankDeadTime(float time)
{
	_timeDead = time;
}