#include "Projectile.h"
#include "Game.h"
#include <math.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

Projectile::Projectile() : GameObject()
{

}

Projectile::~Projectile()
{
	SDL_DestroyTexture(_projectileTexture);
}


void Projectile::Initialize(SDL_Renderer * renderer, const char *fileName)
{
	_projectileTexture = IMG_LoadTexture(renderer, fileName);
	if (_projectileTexture == NULL){
		printf(SDL_GetError());
	}

	_projectilePosition = 
	{ 
		_transform.position.x + 10,
		_transform.position.y + 10 
	};

	_projectileOffSet =
	{
		10 * sinf(MathUtils::ToRadians(_transform.rotation.x +90)), //direction correction 90 degrees
		-10 * cosf(MathUtils::ToRadians(_transform.rotation.x +90))
	};

	_projectileStructure.h = 10;
	_projectileStructure.w = 54;
	_projectileLife = 3;
}

void Projectile::Update(float dt)
{

	if (_projectileLive == true)
	{
		_projectilePosition.x += (_projectileOffSet.x * dt * 20 );
		_projectilePosition.y += (_projectileOffSet.y * dt * 20 );
	}
	if (_projectileLife == 0)
	{
		_projectileLive = false;
		_projectileFired = false;
	}

}

void Projectile::Draw(SDL_Renderer *renderer, float dt)
{
	if (_projectileLive == true)
	{
		_centre = { _projectileStructure.w / 2, _projectileStructure.h / 2 };	
		_projectileStructure.x = _projectilePosition.x + _projectileOffSet.x - _centre.x;
		_projectileStructure.y = _projectilePosition.y + _projectileOffSet.y - _centre.y;
		SDL_RenderCopyEx(renderer, _projectileTexture, NULL, &_projectileStructure, _transform.rotation.x, &_centre, SDL_FLIP_NONE);
	}

}


void Projectile::SetPosition(Vector3 position)
{
	_transform.position = position;
}

Vector3 Projectile::GetPosition()
{
	return this->_transform.position;
}


void Projectile::SetRotation(float rotation)
{
	_transform.rotation.x = rotation;
}
Vector3 Projectile::GetRotation()
{
	return this->_transform.rotation;
}
void Projectile::SetProjectileIsFired(bool isFired)
{
	_projectileFired = isFired;
}

bool Projectile::GetProjectileIsFired( )
{
	return _projectileFired;
}

void Projectile::SetProjectileIsLive(bool isLive)
{
	_projectileLive = isLive;
}

bool Projectile::GetProjectileIsLive()
{
	return _projectileLive;
}

void Projectile::SetProjectileLife(int life)
{
	_projectileLife = life;
}

int Projectile::GetProjectileLife()
{
	return _projectileLife;
}

void Projectile::SetProjectileOffSet(Vector2 offset)
{
	_projectileOffSet = offset;
}
Vector2 Projectile::GetProjectileOffset()
{
	return _projectileOffSet;
}


Vector2 Projectile::GetProjectilePos()
{
	return _projectilePosition;
}
