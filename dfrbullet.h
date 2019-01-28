#pragma once

#ifndef _DFRBULLET_H                 // Prevent multiple definitions if this 
#define _DFRBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace dfrbulletNS
{
	const int WIDTH = 31;                   // image width
	const int HEIGHT = 35;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 300;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 6;           // texture has 8 columns
	const int   DFRBULLET_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFRBULLET_END_FRAME = 5;        // ship1 animation frames 0,1,2,3
	const float DFRBULLET_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class DfrBullet : public Entity
{
private:

public:
	// constructor
	DfrBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void getDir(Entity *to, Entity *from);
	bool collided;
};
#endif
