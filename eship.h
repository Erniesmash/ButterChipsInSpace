#pragma once
#ifndef _ESHIP_H                 // Prevent multiple definitions if this 
#define _ESHIP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "ebullet.h"
using namespace std;

namespace eShipNS
{
	const int WIDTH = 40;                   // image width
	const int HEIGHT = 30;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   ESHIP1_START_FRAME = 0;      // ship1 starts at frame 0
	const int   ESHIP1_END_FRAME = 5;        // ship1 animation frames 0,1,2,3
	const float ESHIP_ANIMATION_DELAY = 0.2f;    // time between frames
	const float ESHIP_SHOT_TIMER = 1.0f;
}

// inherits from Entity class
class EShip : public Entity
{
private:
public:
	// constructor
	EShip();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	float shotTimer;
	vector<EBullet*> ebulletList;
	bool checkCollided;
	void chase(Entity *target);
};
#endif