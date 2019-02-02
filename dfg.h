#pragma once
#ifndef _DFG_H                 // Prevent multiple definitions if this 
#define _DFG_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "dfgbullet.h"
#include "hb.h"
using namespace std;

namespace dfgNS
{
	const int WIDTH = 44;                   // image width44
	const int HEIGHT = 42;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 14;           // texture has 14 columns
	const int   DFG_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFG_END_FRAME = 13;        // ship1 animation frames 0,1,2,3
	const float DFG_ANIMATION_DELAY = 0.12f;    // time between frames
	const float DFG_SHOT_TIMER = 1.0f;
	const int	DFG_HEALTH = 100;
}

// inherits from Entity class
class Dfg : public Entity
{
private:
	TextureManager dfgbTexture;
	DfgBullet dfgb;

	TextureManager hbTexture;
	Hb hb;

public:
	// constructor
	Dfg();
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
	vector<DfgBullet*> dfgbList;
	void shoot();
	bool shot;
	bool dead;
	bool imgChanged;
	float health;

	Game* sw;
};
#endif
