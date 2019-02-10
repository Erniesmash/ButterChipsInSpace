//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once
#ifndef _HB_H                 // Prevent multiple definitions if this 
#define _HB_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace hbNS
{
	const int WIDTH = 30;                   // image width44
	const int HEIGHT = 4;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 14 columns
	const int   HB_START_FRAME = 0;      // ship1 starts at frame 0
	const int   HB_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float HB_ANIMATION_DELAY = 0.12f;    // time between frames
}

// inherits from Entity class
class Hb : public Entity
{
private:

public:
	// constructor
	Hb();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
};
#endif
