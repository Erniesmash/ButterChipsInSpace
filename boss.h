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
	const int	BOSS_HEALTH = 3000;

	//phases
	const float PHASE_ONE = 3000;
	const float PHASE_TWO = 2500;
	const float PHASE_THREE = 2000;
	const float PHASE_FOUR = 1500;
	const float PHASE_FIVE = 1000;
	const float PHASE_SIX = 500;
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
	EBullet eb;
	DfbBullet dfbb;
	DfrBullet dfrb;
	DfgBullet dfgb;
	Skull skull;

	vector<EBullet*> ebList;
	vector<DfbBullet*> dfbbList;
	vector<DfrBullet*> dfrbList;
	vector<DfgBullet*> dfgbList;
	vector<Skull*> skullList;

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

	void phasei() 
	{
		/*float a = 0;
		bool b;
		if (a <= 0)
		{
			b = true;
		}
		else if (a > 45)
		{
			b = false;
		}
		if (b == true)
		{
			a++;
		}
		if (b == false)
		{
			a--;
		}

		for (int i = 1; i < d; i++)
		{
			DfbBullet* d = new DfbBullet;
			d->initialize(sw, dfbbulletNS::WIDTH, dfbbulletNS::HEIGHT, dfbbulletNS::TEXTURE_COLS, &dfbbTexture);
			d->appImpulse(spriteData.x, spriteData.y, 0 + c * i + a);
			dfbbList.push_back(d);
		}*/
	}

	Game* sw;
};
#endif
