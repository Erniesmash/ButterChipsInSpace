//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once

#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 16;                   // image width
	const int HEIGHT = 16;                  // image height
	const float SPEED = 650; 
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   BULLET_START_FRAME = 0;      // bullet starts at frame 0
	const int   BULLET_END_FRAME = 3;        // bullet animation frames 0,1,2,3
	const float BULLET_ANIMATION_DELAY = 0.1f;    // time between frames
	const float QUICKSPEED = 1500;
}

// inherits from Entity class
class Bullet : public Entity
{
private:

public:
	// constructor
	Bullet();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void shoot(Entity *whereFrom, float frameTime);
	bool isFired;

	bool bounceManActive = false;
	bool bounceOnCooldown = false;
	float bounceCooldownTimer = 0;
	float bounceInUseTimer = 4;
};
#endif