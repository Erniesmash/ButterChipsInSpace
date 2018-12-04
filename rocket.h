#ifndef _ROCKET_H                 // Prevent multiple definitions if this 
#define _ROCKET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include <vector>
#include "bullet.h"


namespace rocketNS
{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 29;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float ROTATION_RATE = (float)1.3 * PI; // radians per second
	const float SPEED = 300;                // 100 pixels per second
	const float MASS = 400.0f;              // mass
	const int   TEXTURE_COLS = 1;           // texture has 8 columns
	const int   ROCKET_START_FRAME = 0;      // rocket starts at frame 0
	const int   ROCKET_END_FRAME = 3;        // rocket animation frames 0,1,2,3
	const float ROCKET_ANIMATION_DELAY = 0.2f;    // time between frames
	const float SB_TIMER = 15.0f;
}

// inherits from Entity class
class Rocket : public Entity
{
private:
	bool homingMissleActivated;

public:
	// constructor
	Rocket();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	virtual bool gethomingMissleActivated() const { return homingMissleActivated; }
	virtual void sethomingMissleActivated(bool a) { homingMissleActivated = a; }
	bool sbActive;
	float sbTimer;
	float spd;
};
#endif
