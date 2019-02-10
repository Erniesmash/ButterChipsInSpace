//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _SPECIALS_H                 // Prevent multiple definitions if this 
#define _SPECIALS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace specialsNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height


	const int X = GAME_WIDTH / 100;   // location on screen
	const int Y = GAME_HEIGHT / 100;
	const float ROTATION_RATE = (float)PI / 4;

	const int   TEXTURE_COLS = 4;
	const int   SPECIALS_START_FRAME = 8;
	const int   SPECIALS_END_FRAME = 8;
}

// inherits from Entity class
class Specials : public Entity
{
private:

public:
	// constructor
	Specials();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

};
#endif