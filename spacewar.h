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
#include <string>
#include "powerup.h"
#include "speedboost.h"
#include "explosion.h"
#include "player.h"

#include "textDX.h"
#include "heart.h"
#include "specials.h"
#include "selection.h"

namespace spacewarNS
{
	const char FONT[] = "Arial Bold";  // font
	const char FONT_MENU[] = "Consolas";  // font menu
	const int FONT_BIG_SIZE = 100;     // font height
	const int BUF_SIZE = 200;
	const int FONT_MENU_SIZE = 60;
	const COLOR_ARGB FONT_COLOR = graphicsNS::GREEN;
}


//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
	TextDX dxFont;
	TextDX fontBig;
	TextDX dxFontGreen;
	TextDX fontMenu;

	char buffer[spacewarNS::BUF_SIZE];
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

	TextureManager selectionTexture;
	std::vector<Selection*> selectionList;
	TextureManager heartTexture;
	std::vector<Heart*> heartList;
	// Adjust Starting Number of Lives here
	float numberOfLives = 6;
	float numberOfSpecials = 4;

	TextureManager specialsTexture;
	//Specials meatSpecials;
	std::vector<Specials*> specialList;

	Image	farback;
	Image	starfield;

	Image menu;
	bool menuOn;

	SpeedBoost sb;
	Powerup increaseBulletSpeed;
	Powerup waveShot;
	Player playerMain;
	Rocket	rocketMain;
	Explosion explosion;
	std::vector<Bullet*> bulletList;
	vector<EShip*> eshipList;		// list of enemy ships
	vector<SpeedBoost*> sbList;
	vector<Explosion*> explosionList;
	vector<Powerup*> bulletSpeedPowerupList;
	vector<Powerup*> WaveBulletPowerupList;
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
	void checkEShip();
	void checkSB();
	void checkEB();
	void checkEx();
};

#endif
