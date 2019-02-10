//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once

#ifndef _EBULLET_H                 // Prevent multiple definitions if this 
#define _EBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <cmath>

namespace ebulletNS
{
	const int WIDTH = 10;                   // image width
	const int HEIGHT = 10;                  // image height
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

public:
	// constructor
	EBullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void getDir(float x, float y, float fromx, float fromy, float speed);
	void appImpulse(float xpos, float ypos, float angle, float speed);

	bool collided;
	bool bounce;

};
#endif
