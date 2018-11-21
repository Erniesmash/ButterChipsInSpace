
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

	// initial rocket settings
	rocket.setX(GAME_WIDTH / 2.3);
	rocket.setY(GAME_HEIGHT / 1.15);
	rocket.setFrames(ROCKET_START_FRAME, ROCKET_END_FRAME);   // animation frames          
	rocket.setCurrentFrame(ROCKET_START_FRAME);             // starting frame
	rocket.setFrameDelay(ROCKET_ANIMATION_DELAY);
	rocket.setDegrees(270.0f);                             // angle of ship
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//Rocket Stuff
	rocket.update(frameTime);
	if (rocket.getX() > GAME_WIDTH)               // if off screen right
	{
		rocket.setX((float)-rocket.getWidth());     // position off screen left
	}

	if (input->isKeyDown(ROCKET_RIGHT_KEY))            // if move right
	{
		rocket.setX(rocket.getX() + frameTime * ROCKET_SPEED);
		if (rocket.getX() > GAME_WIDTH)               // if off screen right
			rocket.setX((float)-rocket.getWidth());  // position off screen left
	}

	if (input->isKeyDown(ROCKET_LEFT_KEY))             // if move left
	{
		rocket.setX(rocket.getX() - frameTime * ROCKET_SPEED);
		if (rocket.getX() < -rocket.getWidth())         // if off screen left
			rocket.setX((float)GAME_WIDTH);      // position off screen right
	}

	if (input->isKeyDown(ROCKET_UP_KEY))               // if move up
	{
		rocket.setY(rocket.getY() - frameTime * ROCKET_SPEED);
		if (rocket.getY() < -rocket.getHeight())        // if off screen top
			rocket.setY((float)GAME_HEIGHT);     // position off screen bottom
	}

	if (input->isKeyDown(ROCKET_DOWN_KEY))             // if move down
	{
		rocket.setY(rocket.getY() + frameTime * ROCKET_SPEED);
		if (rocket.getY() > GAME_HEIGHT)              // if off screen bottom
			rocket.setY((float)-rocket.getHeight());    // position off screen top
	}
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



