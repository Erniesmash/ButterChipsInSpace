#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "hb.h"
using namespace std;

namespace bossNS
{
	const int WIDTH = 26 ;                   // image width44
	const int HEIGHT = 33;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 5;           // texture has 14 columns
	const int   BOSS_START_FRAME = 0;      // ship1 starts at frame 0
	const int   BOSS_END_FRAME = 4;        // ship1 animation frames 0,1,2,3
	const float BOSS_ANIMATION_DELAY = 0.12f;    // time between frames
	const float BOSS_SHOT_TIMER = 1.0f;
	const int	BOSS_HEALTH = 100;
}

// inherits from Entity class
class Boss : public Entity
{
private:
	TextureManager bossbTexture;

	TextureManager hbTexture;
	Hb hb;

public:
	// constructor
	Boss();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	float dir(float fromx, float fromy, float tox, float toy);
	void wave();
	void healthBar();
	void chase(Entity *target);
	float shotTimer;
	void shoot();
	bool shot;
	bool dead;
	bool imgChanged;
	float health;

	Game* sw;
};
#endif
