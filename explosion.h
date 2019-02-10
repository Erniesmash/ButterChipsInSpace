//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once

#ifndef _EXPLOSION_H                 // Prevent multiple definitions if this 
#define _EXPLOSION_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace explosionNS
{
	const int WIDTH = 256;                   // image width
	const int HEIGHT = 256;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 300;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   EXPLOSION_START_FRAME = 0;      // ship1 starts at frame 0
	const int   EXPLOSION_END_FRAME = 63;        // ship1 animation frames 0,1,2,3
	const float EXPLOSION_ANIMATION_DELAY = 0.03;    // time between frames
}

// inherits from Entity class
class Explosion : public Entity
{
private:

public:
	// constructor
	Explosion();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	bool exploded;
};
#endif