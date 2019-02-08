#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace playerNS
{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 64;                  // image height
	const int X = GAME_WIDTH / 4 - WIDTH / 4;   // location on screen
	const int Y = GAME_HEIGHT / 4 - HEIGHT / 4;
	//const float ROTATION_RATE = (float)1.3 * PI; // radians per second
	const float SPEED = 300;                // 300 pixels per second
	const float MASS = 400.0f;              // mass
	const int   TEXTURE_COLS = 8;           // texture has 8 columns
	const int   PLAYER_START_FRAME = 0;     // for idle state 
	const int   PLAYER_END_FRAME = 4;        
	const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Player : public Entity
{
private:

public:
	// constructor
	Player();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
};
#endif
