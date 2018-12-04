#pragma once

#ifndef _EBULLET_H                 // Prevent multiple definitions if this 
#define _EBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace ebulletNS
{
	const int WIDTH = 16;                   // image width
	const int HEIGHT = 16;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 300;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   EBULLET_START_FRAME = 0;      // ship1 starts at frame 0
	const int   EBULLET_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float EBULLET_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class EBullet : public Entity
{
private:
	VECTOR2 startpt;
	VECTOR2 endpt;

public:
	// constructor
	EBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	virtual VECTOR2 getvstart() { return startpt; }
	virtual VECTOR2 getvtarget() { return endpt; }
	virtual void setvstart(VECTOR2 start) { start = startpt; }
	virtual void setvtarget(VECTOR2 target) { target = endpt; }
	void getDir(Entity *to, Entity *from);
};
#endif
