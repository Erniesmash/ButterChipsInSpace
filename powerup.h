//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _POWERUP_H                 // Prevent multiple definitions if this 
#define _POWERUP_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
#include "bullet.h"


namespace powerupNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)1.5 * PI; // radians per second
	const float SPEED = 100;                // 100 pixels per second
	const float MASS = 400.0f;              // mass
	const int   TEXTURE_COLS = 4;       

	const int   BULLETSPEED_POWERUP_START_FRAME = 0;    
	const int   BULLETSPEED_POWERUP_END_FRAME = 3;    
	const int   WAVE_POWERUP_START_FRAME = 4;   
	const int   WAVE_POWERUP_END_FRAME = 7;       

	const float POWERUP_ANIMATION_DELAY = 0.4f;    // time between frames
}

// inherits from Entity class
class Powerup : public Entity
{
private:

public:
	// constructor
	Powerup();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
};
#endif
