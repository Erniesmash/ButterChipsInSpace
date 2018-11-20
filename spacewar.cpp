
#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError
	
	// farback texture
	if (!farbackTexture.initialize(graphics, FARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback texture"));

	// farback
	if (!farback.initialize(graphics, 0, 0, 0, &farbackTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback"));

	// rocket texture
	if (!rocketTexture.initialize(graphics, ROCKET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket texture"));

	// rocket
	if (!rocket.initialize(graphics, ROCKET_WIDTH, ROCKET_HEIGHT, ROCKET_COLS, &rocketTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));


	// rocket settings
	rocket.setX(GAME_WIDTH / 4);
	rocket.setY(GAME_HEIGHT / 4);
	rocket.setFrames(ROCKET_START_FRAME, ROCKET_END_FRAME);   // animation frames          
	rocket.setCurrentFrame(ROCKET_START_FRAME);             // starting frame
	rocket.setFrameDelay(ROCKET_ANIMATION_DELAY);
	rocket.setDegrees(45.0f);                             // angle of ship
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	farback.draw(); // add background to scene
	rocket.draw(); // add rocket to scene

	graphics->spriteEnd();                  // end drawing sprites
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	farbackTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	farbackTexture.onResetDevice();

    Game::resetAll();
    return;
}



