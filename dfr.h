#pragma once
#ifndef _DFR_H                 // Prevent multiple definitions if this 
#define _DFR_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "dfrbullet.h"
using namespace std;

namespace dfrNS
{
	const int WIDTH = 44;                   // image width44
	const int HEIGHT = 42;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 14;           // texture has 14 columns
	const int   DFR_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFR_END_FRAME = 13;        // ship1 animation frames 0,1,2,3
	const float DFR_ANIMATION_DELAY = 0.12f;    // time between frames
	const float DFR_SHOT_TIMER = 1.0f;
	const int	DFR_HEALTH = 100;
}

// inherits from Entity class
class Dfr : public Entity
{
private:
	TextureManager dfrbTexture;
	DfrBullet dfrb;

public:
	// constructor
	Dfr();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	float shotTimer;
	vector<DfrBullet*> dfrbList;
	bool checkCollided;
	void chase(Entity *target);
	void shoot();
	bool shot;
	float health;
	float dir(float fromx, float fromy, float tox, float toy);
	void wave();
	void healthBar();
	Game* sw;
};
#endif
