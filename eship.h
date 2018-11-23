#pragma once
#ifndef _ESHIP_H                 // Prevent multiple definitions if this 
#define _ESHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace eShipNS
{
	const int WIDTH = 40;                   // image width
	const int HEIGHT = 30;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)PI / 4; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   ESHIP1_START_FRAME = 0;      // ship1 starts at frame 0
	const int   ESHIP1_END_FRAME = 5;        // ship1 animation frames 0,1,2,3
	const float ESHIP_ANIMATION_DELAY = 0.1f;    // time between frames
	const int   SHIELD_START_FRAME = 24;    // shield start frame
	const int   SHIELD_END_FRAME = 27;      // shield end frame
	const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}

// inherits from Entity class
class EShip : public Entity
{
private:
	bool    shieldOn;
	Image   shield;
public:
	// constructor
	EShip();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void damage(WEAPON);
};
#endif