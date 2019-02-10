//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once

#ifndef _DFGBULLET_H                 // Prevent multiple definitions if this 
#define _DFGBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace dfgbulletNS
{
	const int WIDTH = 10;                   // image width
	const int HEIGHT = 10;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 600;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   DFGBULLET_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFGBULLET_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float DFGBULLET_ANIMATION_DELAY = 0;    // time between frames
}

// inherits from Entity class
class DfgBullet : public Entity
{
private:

public:
	// constructor
	DfgBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	bool collided;
	bool bounce;
	void getDir(float x, float y, float fromx, float fromy, float speed);
	void appImpulse(float xpos, float ypos, double angle, float speed);
};
#endif
