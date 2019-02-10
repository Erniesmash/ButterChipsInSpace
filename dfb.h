//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once
#ifndef _DFB_H                 // Prevent multiple definitions if this 
#define _DFB_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "dfbbullet.h"
#include "hb.h"
using namespace std;

namespace dfbNS
{
	const int WIDTH = 44;                   // image width44
	const int HEIGHT = 42;                  // image height42
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)0; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 300.0f;              // mass
	const int   TEXTURE_COLS = 14;           // texture has 14 columns
	const int   DFB_START_FRAME = 0;      // ship1 starts at frame 0
	const int   DFB_END_FRAME = 13;        // ship1 animation frames 0,1,2,3
	const float DFB_ANIMATION_DELAY = 0.12f;    // time between frames
	const float DFB_SHOT_TIMER = 1.0f;
	const int	DFB_HEALTH = 1000;
	const float DFB_SPREAD_ANGLE = 5;
	const float DFB_ANGLE = 135;
	const int BULLET_COUNT = 15;
}

// inherits from Entity class
class Dfb : public Entity
{
private:
	TextureManager dfbbTexture;
	DfbBullet dfbb;

	TextureManager hbTexture;
	Hb hb;

public:
	// constructor
	Dfb();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	float shotTimer;
	vector<DfbBullet*> dfbbList;
	void shoot();
	bool shot;
	bool dead;
	bool imgChanged;
	float health;
	float a;

	Game* sw;

	void checkBullet()
	{
		for (vector<DfbBullet*>::iterator it = dfbbList.begin();
			it != dfbbList.end();)
		{
			if ((*it)->collided == true)
			{
				SAFE_DELETE(*it);
				it = dfbbList.erase(it);
			}

			else
			{
				++it;
			}
		}
	}
};
#endif
