//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "bullet.h"
#include "ebullet.h"
#include <vector>
#include "explosion.h"
#include "player.h"

//enemies
#include "dfr.h"
#include "dfb.h"
#include "dfg.h"
#include "skull.h"
#include "boss.h"

#include "hb.h"

#include "textDX.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
	TextDX dxFont;
    TextureManager gameTextures;    // game texture
	TextureManager farbackTexture;	// farback texture
	TextureManager bulletTexture;	// bullet texture
	TextureManager ebulletTexture;	// enemy bullet texure
	TextureManager starfieldTexture;
	TextureManager explosionTexture;
	TextureManager playerTexture;

	//enemy texture
	TextureManager dfrTexture;
	TextureManager dfbTexture;
	TextureManager dfgTexture;
	TextureManager skullTexture;
	TextureManager bossTexture;
	TextureManager ebTexture;

	//enemy health
	TextureManager ehealthTexture;

	Image	farback;
	Image	starfield;

	Player playerMain;

	Explosion explosion;

	TextureManager hbTexture;
	Hb hb;

	std::vector<Bullet*> bulletList;
	vector<Explosion*> explosionList;

	//enemies
	Dfr dfr;
	Dfb dfb;
	Dfg dfg;
	Skull skull;
	Boss boss;

	//enemy vectors
	vector<Dfr*> dfrList;
	vector<Dfb*> dfbList;
	vector<Dfg*> dfgList;
	vector<Skull*> skullList;
	vector<Boss*> bossList;
	vector<EBullet*> ebList;

	float sbSpawnTime = 0.0f;
	float waitTimer = 0.0f;
	float bulletSpeedTime = 0.0f;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	// kill enemy
	void checkDfr();
	void checkDfb();
	void checkDfg();
	void checkSkull();
	void checkBoss();

	// spawn enemy
	void spawnDfr(float x, float y)
	{
		Dfr* r = new Dfr;
		r->initialize(this, dfrNS::WIDTH, dfrNS::HEIGHT, dfrNS::TEXTURE_COLS, &dfrTexture);
		r->setX(GAME_WIDTH / 2);
		r->setY(GAME_HEIGHT / 5);
		dfrList.push_back(r);
	}

	void spawnDfb(float x, float y)
	{
		Dfb* b = new Dfb;
		b->initialize(this, dfbNS::WIDTH, dfbNS::HEIGHT, dfbNS::TEXTURE_COLS, &dfbTexture);
		b->setX(x);
		b->setY(y);
		dfbList.push_back(b);
	}

	void spawnDfg(float x, float y, float start, float end)
	{
		Dfg* g = new Dfg;
		g->initialize(this, dfgNS::WIDTH, dfgNS::HEIGHT, dfgNS::TEXTURE_COLS, &dfgTexture);
		g->setX(x);
		g->setY(y);
		g->startheight = start;
		g->endheight = end;
		dfgList.push_back(g);
	}

	void spawnSkull(float x, float y)
	{
		Skull* skull = new Skull;
		skull->initialize(this, skullNS::WIDTH, skullNS::HEIGHT, skull->textcols, &skullTexture);
		skull->setX(x);
		skull->setY(y);
		skullList.push_back(skull);
	}

	void spawnBoss(float x, float y)
	{
		Boss* boss = new Boss;
		boss->initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture);
		boss->setX(x);
		boss->setY(y);
		bossList.push_back(boss);
	}
};

#endif
