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
#include "rocket.h"
#include "bullet.h"
#include "eship.h"
#include "ebullet.h"
#include <vector>
#include "powerup.h"
#include "speedboost.h"
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
	TextureManager rocketTexture;	// rocket texture
	TextureManager farbackTexture;	// farback texture
	TextureManager bulletTexture;	// bullet texture
	TextureManager eShipTexture;	// enemy ship texture
	TextureManager ebulletTexture;	// enemy bullet texure
	TextureManager starfieldTexture;
	TextureManager powerupTexture;
	TextureManager sbTexture;
	TextureManager explosionTexture;
	TextureManager playerTexture;

	//enemy texture
	TextureManager dfrTexture;
	TextureManager dfbTexture;
	TextureManager dfgTexture;
	TextureManager skullTexture;
	TextureManager bossTexture;

	//enemy health
	TextureManager ehealthTexture;

	Image	farback;
	Image	starfield;

	SpeedBoost sb;
	//Powerup increaseBulletSpeed;
	Powerup waveShot;

	Player playerMain;
	Rocket	rocketMain;
	EShip	eShip;			// enemy ship

	Explosion explosion;

	TextureManager hbTexture;
	Hb hb;

	std::vector<Bullet*> bulletList;
	vector<EShip*> eshipList;		// list of enemy ships
	vector<SpeedBoost*> sbList;
	vector<Explosion*> explosionList;
	vector<Powerup*> bulletSpeedPowerupList;
	vector<Powerup*> WaveBulletPowerupList;

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

	//void checkBullet()
};

#endif
