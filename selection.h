//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#ifndef _SELECTION_H                 // Prevent multiple definitions if this 
#define _SELECTION_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace selectionNS
{
	const int WIDTH = 34;                   // image width
	const int HEIGHT = 34;                  // image height


	const int X = GAME_WIDTH / 100;   // location on screen
	const int Y = GAME_HEIGHT / 100;
	const float ROTATION_RATE = (float)PI / 4;

	const int   TEXTURE_COLS = 1;
	const int   SELECTION_START_FRAME = 0;
	const int   SELECTION_END_FRAME = 0;
}

// inherits from Entity class
class Selection : public Entity
{
private:

public:
	// constructor
	Selection();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);

};
#endif
