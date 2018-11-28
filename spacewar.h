#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "ship.h"
#include "rocket.h"
#include "bullet.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	TextureManager rocketTexture;	// rocket texture
	TextureManager farbackTexture;	// farback texture
	TextureManager bulletTexture;	// bullet texture
    Ship    ship1, ship2;           // spaceships
	Rocket	rocketMain;
    Planet  planet;         // the planet
    Image   nebula;         // backdrop image
	Image	farback;		// farback image
	Bullet bullet;			// the bullet

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
};

#endif
