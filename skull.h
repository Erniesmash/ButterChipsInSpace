#pragma once
#ifndef _SKULL_H                 // Prevent multiple definitions if this 
#define _SKULL_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "hb.h"
#include "ebullet.h"
using namespace std;

namespace skullNS
{
	// entrance/death
	const int WIDTH = 37;                   // image width44
	const int HEIGHT = 42;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 14 columns
	const int   SKULL_START_FRAME = 0;      // ship1 starts at frame 0
	const int   SKULL_END_FRAME = 8;        // ship1 animation frames 0,1,2,3
	const float SKULL_ANIMATION_DELAY = 0.12f;    // time between frames
	const float SKULL_SHOT_TIMER = 0.10f;
	const int	SKULL_HEALTH = 100;

	//active
	const int	ACTIVE_WIDTH = 20;
	const int	ACTIVE_HEIGHT = 25;
	const int	ACTIVE_TEXTURE_COLS = 2;
	const int	ACTIVE_START_FRAME = 0;
	const int	ACTIVE_END_FRAME = 1;
}

// inherits from Entity class
class Skull : public Entity
{
private:
	TextureManager skullbTexture;

	TextureManager hbTexture;
	Hb hb;

	vector<EBullet*> ebList;

public:
	// constructor
	Skull();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void chase(Entity *target);

	bool exited;
	bool dead;
	bool imgChanged;
	bool entered;
	bool enteredChanged;
	bool active;
	int textcols;
	float health;

	Entity* player;
	Game* sw;

	void getPlayer(Entity* target)
	{
		player = target;
	}
};
#endif
