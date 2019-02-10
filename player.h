//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <string>


namespace playerNS
{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 64;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)1.3 * PI; // radians per second
	const float SPEED = 400;
	const float MASS = 400.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   PLAYER_START_FRAME = 0;     // for idle state 
	const int   PLAYER_END_FRAME = 4;        
	const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames

	const int   SHIELD_START_FRAME = 0;   
	const int   SHIELD_END_FRAME = 0;    
	const float SHIELD_ANIMATION_DELAY = 0.1f; 
	const int   SHIELD_WIDTH = 269;    
	const int   SHIELD_HEIGHT = 269;   
	const int SHIELD_COLS = 1;
}

// inherits from Entity class
class Player : public Entity
{
private:
	
	TextureManager shieldTexture;
	bool    shieldOn;
	Image   shield;

public:
	// constructor
	Player();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	void setShieldOn(bool sh) { shieldOn = sh; }
	bool getShieldOn() { return shieldOn; }

	float dashCooldownTimer = 0;
	float dashInUseTimer = 0.5;
	bool dashOnCooldown = false;
	bool dashActive = false;

	float shieldCooldownTimer = 0;
	float shieldInUseTimer = 3;
	bool shieldOnCooldown = false;

	int dialogueChoice;
	const char * playerDialogue;
	bool dialogueEnd;

	int health;
};
#endif
