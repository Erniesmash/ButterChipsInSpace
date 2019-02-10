//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _HEART_H                 // Prevent multiple definitions if this 
#define _HEART_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace heartNS
{
	const int WIDTH = 136;                   // image width
	const int HEIGHT = 120;                  // image height


	const int X = 0;   // location on screen
	const int Y = 0;
	const float ROTATION_RATE = (float)PI / 4;
	const float MASS = 300.0f;

	const int   TEXTURE_COLS = 1;
	const int   HEART_START_FRAME = 0;
	const int   HEART_END_FRAME = 0;
}

// inherits from Entity class
class Heart : public Entity
{
private:

public:
	// constructor
	Heart();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

};
#endif