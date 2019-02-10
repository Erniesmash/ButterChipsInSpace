//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "entity.h"
#include "constants.h"
#include "ebullet.h"
#include "dfbbullet.h"
#include "dfrbullet.h"
#include "dfgbullet.h"
#include "skull.h"
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
	const int	BOSS_HEALTH = 22500;

	//phases
	const float PHASE_ONE = 22500;
	const float PHASE_TWO = 18750;
	const float PHASE_THREE = 15000;
	const float PHASE_FOUR = 11250;
	const float PHASE_FIVE = 7500;
	const float PHASE_SIX = 3750;
}

// inherits from Entity class
class Boss : public Entity
{
private:
	TextureManager ebTexture;
	TextureManager hbTexture;

	TextureManager dfbbTexture;
	TextureManager dfrbTexture;
	TextureManager dfgbTexture;
	TextureManager skullTexture;

	Hb hb;

public:
	// constructor
	Boss();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	float shotTimer;
	//void shoot();
	bool shot;
	bool dead;
	bool imgChanged;
	float health;
	float timer;
	float pTime;

	vector<EBullet*> ebList;
	vector<DfbBullet*> dfbbList;
	vector<DfrBullet*> dfrbList;
	vector<DfgBullet*> dfgbList;
	vector<Skull*> skullList;

	Game* sw;
	Entity* player;

	void getPlayer(Entity* target)
	{
		player = target;
	}

	void checkBullet()
	{
		for (vector<DfrBullet*>::iterator it = dfrbList.begin();
			it != dfrbList.end();)
		{
			if ((*it)->collided == true)
			{
				SAFE_DELETE(*it);
				it = dfrbList.erase(it);
			}

			else
			{
				++it;
			}
		}

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

		for (vector<DfgBullet*>::iterator it = dfgbList.begin();
			it != dfgbList.end();)
		{
			if ((*it)->collided == true)
			{
				SAFE_DELETE(*it);
				it = dfgbList.erase(it);
			}

			else
			{
				++it;
			}
		}

		for (vector<EBullet*>::iterator it = ebList.begin();
			it != ebList.end();)
		{
			if ((*it)->collided == true)
			{
				SAFE_DELETE(*it);
				it = ebList.erase(it);
			}

			else
			{
				++it;
			}
		}
	}
};
#endif
