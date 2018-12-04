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

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager gameTextures;    // game texture
	TextureManager rocketTexture;	// rocket texture
	TextureManager farbackTexture;	// farback texture
	TextureManager bulletTexture;	// bullet texture
	TextureManager eShipTexture;	// enemy ship texture
	TextureManager ebulletTexture;	// enemy bullet texure
	TextureManager starfieldTexture;
	TextureManager powerupTexture;
	TextureManager sbTexture;

	SpeedBoost sb;
	Powerup homingMissle;
	Rocket	rocketMain;
	Image	farback;
	Image	starfield;

	EShip	eShip;			// enemy ship
	EBullet	ebullet;			// enemy bullet

	std::vector<Bullet*> bulletList;
	vector<EShip*> eshipList;		// list of enemy ships
	vector<EBullet*> ebulletList;
	vector<SpeedBoost*> sbList;
	float sbSpawnTime = 0.0f;
	float waitTimer = 0;

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
	void checkEShip();
	void checkSB();
	void checkEB();
	//void checkBullet()
};

#endif
