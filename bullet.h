#pragma once

#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 16;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI / 2; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   BULLET_START_FRAME = 0;      // bullet starts at frame 0
	const int   BULLET_END_FRAME = 3;        // bullet animation frames 0,1,2,3
	const float BULLET_ANIMATION_DELAY = 0.2f;    // time between frames
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
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
};

#endif