#pragma once

#ifndef _DFBBULLET_H                 // Prevent multiple definitions if this 
#define _DFBBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace dfbbulletNS
{
	const int WIDTH = 16;                   // image width
	const int HEIGHT = 16;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 300;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   DFBBULLET_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFBBULLET_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float DFBBULLET_ANIMATION_DELAY = 0;    // time between frames
}

// inherits from Entity class
class DfbBullet : public Entity
{
private:

public:
	// constructor
	DfbBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void getDir(Entity *to, Entity *from);
	bool collided;
	void appImpulse(float xpos, float ypos, float ximp, float yimp);
	bool invert;
	void wavy(Entity* from);
};
#endif
