#include "Game.h"
#include "InputManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <istream>
const char *player1FilePath = "res/loltanks.bmp";
const char *player2FilePath = "res/loltanks2.bmp";
const char *projectileFilePath = "res/Upgrade_missle.bmp";
// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
}

void Game::InitializeImpl(SDL_Renderer * renderer)
{
	printf("User Controls \n ---------- \n Player 1(Blue tank) \n Arrow keys to move forward,rotate and back. numlock 0 to fire. \n Player 2(Red tank) \n WASD keys to maneuver spacebar to fire.\n");
	//Outer wall
	_wall1.x = 10;
	_wall1.y = 10;
	_wall1.w = 620;
	_wall1.h = 620;
	//Centre wall
	_wall2.x = 242;
	_wall2.y = 242;
	_wall2.w = 152;
	_wall2.h = 152;
	
	//Set Score
	_player1Score = 0;
	_player2Score = 0;

	//Set Window Title and Score
	sprintf_s(_score, "Player 1(Blue): %d --------------- LolTanks --------------- Player 2(Red): %d", _player1Score, _player2Score);
	SDL_SetWindowTitle(_window, _score);

	//Bitmaps for textures
	_player1.Initialize(renderer, player1FilePath);
	_player2.Initialize(renderer, player2FilePath);
	///////
	_speed = _player1.GetPlayerSpeed();
	_player1Radians = 20; //Initial directions set here
	_player2Radians = 180;
	//initialize players to default positions
	_player1Pos = { 50.0f, 50.0f, 0.0f };
	_player2Pos = { 540.0f, 560.0f, 0.0f };
	_rotSpeed = 1.0f;

	_player1.SetPosition(_player1Pos);
	_player2.SetPosition(_player2Pos);
	_player1.SetPlayerRotationSpeed(_rotSpeed);
	_player1.SetPlayerRotationSpeed(_rotSpeed);
}

void Game::UpdateImpl(float dt)
{
	InputManager *im1 = InputManager::GetInstance();
	InputManager *im2 = InputManager::GetInstance();
	im1->Update(dt);

	_player1DirectionVec = { cos(_player1Radians), sin(_player1Radians) };
	_player1.SetDirectionVector(_player1DirectionVec);
	if (_player1.GetTankIsDead() == false){

		// Check for user input.
		if (im1->IsKeyDown(SDLK_UP) == true) // move forward towards the positive direction
		{
			_player1Pos.x += _speed * _player1.GetDirectionVector().x * dt;
			_player1Pos.y += _speed * _player1.GetDirectionVector().y * dt;
		}
		if (im1->IsKeyDown(SDLK_DOWN) == true) // move forward towards the negative direction
		{
			_player1Pos.x -= _speed * _player1.GetDirectionVector().x * dt;
			_player1Pos.y -= _speed * _player1.GetDirectionVector().y * dt;
		}
		if (im1->IsKeyDown(SDLK_LEFT) == true) // rotate 10 degrees to the left
		{
			_player1Radians -= _rotSpeed * dt;

		}
		if (im1->IsKeyDown(SDLK_RIGHT) == true) // rotate 10 degrees to the right
		{
			_player1Radians += _rotSpeed * dt;
		}
		if (_player2.GetTankIsDead() == false){
			if (im1->IsKeyDown(SDLK_KP_0) == true)
			{
				_player1.projectile.SetProjectileIsFired(true);
			}
		}
	}
	////////////////////////////
	//Player 2
	/////////////////////////////
	im2->Update(dt);
	_player2DirectionVec = { cos(_player2Radians), sin(_player2Radians) };
	_player2.SetDirectionVector(_player2DirectionVec);
	if (_player2.GetTankIsDead() == false){

		if (im2->IsKeyDown(SDLK_w) == true) // move forward towards the positive direction
		{
			_player2Pos.x += _speed * _player2.GetDirectionVector().x * dt;
			_player2Pos.y += _speed * _player2.GetDirectionVector().y * dt;
		}
		if (im2->IsKeyDown(SDLK_s) == true) // move forward towards the negative direction
		{
			_player2Pos.x -= _speed * _player2.GetDirectionVector().x * dt;
			_player2Pos.y -= _speed * _player2.GetDirectionVector().y * dt;
		}
		if (im2->IsKeyDown(SDLK_a) == true) // rotate 10 degrees to the left
		{
			_player2Radians -= _rotSpeed * dt;
		}
		if (im2->IsKeyDown(SDLK_d) == true) // rotate 10 degrees to the right
		{
			_player2Radians += _rotSpeed * dt;
		}
		if (_player1.GetTankIsDead() == false){
			if (im2->IsKeyDown(SDLK_SPACE) == true)
			{
				_player2.projectile.SetProjectileIsFired(true);
			}
		}
	}
	 Collision();

	_player1.SetPosition(_player1Pos);
	_player1.SetPlayerRotation(_player1Radians);
	_player2.SetPosition(_player2Pos);
	_player2.SetPlayerRotation(_player2Radians);
	_player1.Update(dt);
	_player2.Update(dt);

	if (_player1.projectile.GetProjectileIsLive())
	{
		_player1.projectile.Update(dt);
	}
	if (_player2.projectile.GetProjectileIsLive())
	{
		_player2.projectile.Update(dt);
	}
}


void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
	// Set the draw colour for screen clearing.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	RenderWorldWalls(renderer,&_wall1,&_wall2);

	_player1.Draw(renderer, dt);

	_player2.Draw(renderer, dt);

	if (_player1.projectile.GetProjectileIsFired() == true && _player1.projectile.GetProjectileIsLive() == false && _player2.GetTankIsDead() == false)
	{
		_player1.projectile.SetPosition(_player1.GetPosition());
		_player1.projectile.SetRotation(_player1.GetPlayerRotation());
		_player1.projectile.Initialize(renderer,projectileFilePath);
		_player1.projectile.SetProjectileIsLive(true);
		_player1.projectile.SetProjectileIsFired(false);
	}

	if (_player1.projectile.GetProjectileIsLive() == true )
	{
		_player1.projectile.Draw(renderer, dt);
	}

	if (_player2.projectile.GetProjectileIsFired() == true && _player2.projectile.GetProjectileIsLive() == false && _player1.GetTankIsDead() == false)
	{
		_player2.projectile.SetPosition(_player2.GetPosition());
		_player2.projectile.SetRotation(_player2.GetPlayerRotation());
		_player2.projectile.Initialize(renderer, projectileFilePath);
		_player2.projectile.SetProjectileIsLive(true);
		_player2.projectile.SetProjectileIsFired(false);
	}

	if (_player2.projectile.GetProjectileIsLive() == true )
	{		
		_player2.projectile.Draw(renderer, dt);
	}


	// Present what is in our renderer to our window.
	SDL_RenderPresent(renderer);
}

void Game::RenderWorldWalls(SDL_Renderer* renderer, SDL_Rect *wall1, SDL_Rect *wall2)
{
	SDL_RenderDrawRect(renderer, wall1); // Outer wall
	SDL_RenderDrawRect(renderer, wall2); // Centre wall
}


void Game::Collision()
{
	if (_player1.projectile.GetProjectileIsLive() == true)
	{
		int x1, y1, x2,y2;
		x1 = _player1.projectile.GetProjectilePos().x;
		y1 = _player1.projectile.GetProjectilePos().y;
		x2 = (_player1.projectile.GetProjectilePos().x + _player1.projectile.GetProjectileOffset().x);
		y2 = (_player1.projectile.GetProjectilePos().y + _player1.projectile.GetProjectileOffset().y);
		GetPlayerProjectilePos(&_player1, x1, x2, y1, y2);

		if (SDL_IntersectRectAndLine(&_player2.GetTankRect(), (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true) //Player 1 projectile hits player 2 and scores 10 points
		{
			_player1.projectile.SetProjectileIsLive(false);
			_player1.projectile.SetProjectileIsFired(false);
			_player2.SetTankIsDead(true);
			_player2.SetTankDeadTime(3.0f);
			_player1Score += 10;
			sprintf_s(_score, "Player 1(Blue): %d --------------- LolTanks --------------- Player 2(Red): %d", _player1Score, _player2Score);
			SDL_SetWindowTitle(_window, _score);
		}

		if (SDL_IntersectRectAndLine(&_wall2, (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true)//Player 1 projectile bounces off wall1
		{
			_player1.projectile.SetProjectileOffSet({ _player1.projectile.GetProjectileOffset().x * -1, _player1.projectile.GetProjectileOffset().y * -1 });
			_player1.projectile.SetRotation(_player1.projectile.GetRotation().x *-1);
			_player1.projectile.SetProjectileLife(_player1.projectile.GetProjectileLife() - 1);
		}

		if (!SDL_IntersectRectAndLine(&_wall1, (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true)//Player 1 projectile bounces off wall1
		{
			_player1.projectile.SetProjectileOffSet({ _player1.projectile.GetProjectileOffset().x * -1, _player1.projectile.GetProjectileOffset().y * -1 });
			_player1.projectile.SetRotation(_player1.projectile.GetRotation().x *-1);
			_player1.projectile.SetProjectileLife(_player1.projectile.GetProjectileLife() - 1);
		}
	}

	if (_player2.projectile.GetProjectileIsLive() == true)
	{
		int x1, y1, x2, y2;
		x1 = _player2.projectile.GetProjectilePos().x;
		y1 = _player2.projectile.GetProjectilePos().y;
		x2 = (_player2.projectile.GetProjectilePos().x + _player2.projectile.GetProjectileOffset().x);
		y2 = (_player2.projectile.GetProjectilePos().y + _player2.projectile.GetProjectileOffset().y);
		GetPlayerProjectilePos(&_player2, x1, x2, y1, y2);

		if (SDL_IntersectRectAndLine(&_player1.GetTankRect(), (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true)//Player 2 projectile hits player 1 and scores 10 points
		{
			_player2.projectile.SetProjectileIsLive(false);
			_player2.projectile.SetProjectileIsFired(false);
			_player1.SetTankIsDead(true);;
			_player1.SetTankDeadTime(3.0f);
			_player2Score += 10;
			sprintf_s(_score, "Player 1(Blue): %d --------------- LolTanks --------------- Player 2(Red): %d", _player1Score, _player2Score);
			SDL_SetWindowTitle(_window, _score);
		}

		if (SDL_IntersectRectAndLine(&_wall2, (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true)//Player 2 projectile bounces wall2
		{		

			_player2.projectile.SetProjectileOffSet({ _player2.projectile.GetProjectileOffset().x * -1, _player2.projectile.GetProjectileOffset().y * -1 });
			_player2.projectile.SetRotation(_player2.projectile.GetRotation().x *-1);
			_player2.projectile.SetProjectileLife(_player2.projectile.GetProjectileLife() - 1);
		}

		if (!SDL_IntersectRectAndLine(&_wall1, (int*)&x1, (int*)&y1, (int*)&x2, (int*)&y2) == true)//Player 2 projectile bounces off wall1
		{

			_player2.projectile.SetProjectileOffSet({ _player2.projectile.GetProjectileOffset().x * -1, _player2.projectile.GetProjectileOffset().y * -1 });
			_player2.projectile.SetRotation(_player2.projectile.GetRotation().x *-1);
			_player2.projectile.SetProjectileLife(_player2.projectile.GetProjectileLife() - 1);
		}
	}

	////// Tank bumps tank
	if (SDL_HasIntersection(&_player1.GetTankRect(), &_player2.GetTankRect()) == true)
	{
		if (_player1Pos.x < _player2Pos.x)//Player 1 left of other 2 player || Player 1 below Player 2 
		{
			_player1Pos.x -= 2;
			_player2Pos.x += 2;
		}
		if (_player1Pos.x > _player2Pos.x)
		{
			_player1Pos.x += 2;
			_player2Pos.x -= 2;
		}
		if (_player1Pos.y > _player2Pos.y)
		{
			_player1Pos.y += 2;
			_player2Pos.y -= 2;
		}
		if (_player1Pos.y < _player2Pos.y)
		{
			_player1Pos.y -= 2;
			_player2Pos.y += 2;
		}
	}
	if (!SDL_HasIntersection(&_player1.GetTankRect(), &_wall1))
	{
		if (_player1Pos.x < _wall1.x)//Player 1 left of other wall1
		{
			_player1Pos.x += 2;
		}
		if (_player1Pos.x > _wall1.x)//Player 1 right of other wall1
		{
			_player1Pos.x -= 2;
		}
		if (_player1Pos.y > _wall1.y)//Player 1 top of other wall1
		{
			_player1Pos.y -= 2;
		}
		if (_player1Pos.y < _wall1.y)//Player 1 bottom of other wall1
		{
			_player1Pos.y += 2;
		}
	
	}

	if (!SDL_HasIntersection(&_player2.GetTankRect(), &_wall1))
	{
		if (_player2Pos.x < _wall1.x)//Player 2 left of other wall1
		{
			_player2Pos.x += 2;
		}
		if (_player2Pos.x > _wall1.x)//Player 2 right of other wall1
		{
			_player2Pos.x -= 2;
		}
		if (_player2Pos.y > _wall1.y)//Player 2 top of other wall1
		{
			_player2Pos.y -= 2;
		}
		if (_player2Pos.y < _wall1.y)//Player 2 bottom of other wall1
		{
			_player2Pos.y += 2;
		}

	}

	if (SDL_HasIntersection(&_player1.GetTankRect(), &_wall2))
	{
		if (_player1Pos.x < _wall2.x )//Player 1 left of other wall2
		{
			_player1Pos.x -= 2;
		}
		if (_player1Pos.x > _wall2.x)//Player 1 right of other wall2
			{
			_player1Pos.x += 2;
			}
		if (_player1Pos.y > _wall2.y)//Player 1 top of other wall2
		{
			_player1Pos.y += 2;
		}
		if (_player1Pos.y < _wall2.y)//Player 1 bottom of other wall2
		{
			_player1Pos.y -= 2;
		}
	}

	if (SDL_HasIntersection(&_player2.GetTankRect(), &_wall2))
	{
		if (_player2Pos.x < _wall2.x)//Player 2 left of other wall2
		{
			_player2Pos.x -= 2;
		}
		if (_player2Pos.x > _wall2.x)//Player 2 right of other wall2
		{
			_player2Pos.x += 2;
		}
		if (_player2Pos.y > _wall2.y)//Player 2 top of other wall2
		{
			_player2Pos.y += 2;
		}
		if (_player2Pos.y < _wall2.y)//Player 2 bottom of other wall2
		{
			_player2Pos.y -= 2;
		}
	}
}

void Game::GetPlayerProjectilePos(Player *player, float x1, float x2, float y1, float y2)
{
	x1 =  (player->projectile.GetProjectilePos().x);
	x2 = (player->projectile.GetProjectilePos().x + player->projectile.GetProjectileOffset().x);
	y1 = (player->projectile.GetProjectilePos().y);
	y2 = (player->projectile.GetProjectilePos().y + player->projectile.GetProjectileOffset().y);
}