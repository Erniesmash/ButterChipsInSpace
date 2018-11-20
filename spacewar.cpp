
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

	// nebula texture
	if (!nebulaTexture.initialize(graphics, NEBULA_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics, PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// spaceship texture
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// spaceship2 texture
	if (!ship2Texture.initialize(graphics, SHIP_IMAGE2))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// nebula
	if (!nebula.initialize(graphics, 0, 0, 0, &nebulaTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(graphics, 0, 0, 0, &planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	// place planet in center of screen
	planet.setX(GAME_WIDTH*0.5f - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	// ship
	if (!ship.initialize(graphics, SHIP_WIDTH, SHIP_HEIGHT, SHIP_COLS, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	// ship settings
	ship.setX(GAME_WIDTH / 4);              // start above and left of planet
	ship.setY(GAME_HEIGHT / 4);
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             
	ship.setCurrentFrame(SHIP_START_FRAME);             // starting frame
	ship.setFrameDelay(SHIP_ANIMATION_DELAY);
	ship.setDegrees(45.0f);                             // angle of ship

	// ship2
	if (!ship2.initialize(graphics, SHIP2_WIDTH, SHIP2_HEIGHT, SHIP2_COLS, &ship2Texture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	// ship2 settings
	ship2.setX(GAME_WIDTH / 3); 
	ship2.setY(GAME_HEIGHT / 2);
	ship2.setFrames(SHIP2_START_FRAME, SHIP2_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             
	ship2.setCurrentFrame(SHIP2_START_FRAME);             // starting frame
	ship2.setFrameDelay(SHIP2_ANIMATION_DELAY);
	ship2.setDegrees(45.0f);                             // angle of ship
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	ship.update(frameTime);
	ship2.update(frameTime);

	/*
	// rotate ship
	ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);
	// make ship smaller
	ship.setScale(ship.getScale() - frameTime * SCALE_RATE);
	// move ship right
	ship.setX(ship.getX() + frameTime * SHIP_SPEED);
	if (ship.getX() > GAME_WIDTH)               // if off screen right
	{
		ship.setX((float)-ship.getWidth());     // position off screen left
		ship.setScale(SHIP_SCALE);              // set to starting size
	}
	*/
	// move ship right
	ship2.setX(ship2.getX() + frameTime * v);
	if (ship2.getX() > GAME_WIDTH)               // if off screen right
	{
		ship2.setX((float)-ship2.getWidth());     // position off screen left
	}

	if (input->isKeyDown(SHIP_RIGHT_KEY))            // if move right
	{
		v++;
		ship.setX(ship.getX() + frameTime * SHIP_SPEED);
		if (ship.getX() > GAME_WIDTH)               // if off screen right
			ship.setX((float)-ship.getWidth());  // position off screen left
		//ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE);

		if (ship2.getX() > GAME_WIDTH)               // if off screen right
			ship2.setX((float)-ship2.getWidth());  // position off screen left
		ship2.setDegrees(ship2.getDegrees() + frameTime * ROTATION_RATE2);
	}

	if (input->isKeyDown(SHIP_LEFT_KEY))             // if move left
	{
		v--;
		ship.setX(ship.getX() - frameTime * SHIP_SPEED);
		if (ship.getX() < -ship.getWidth())         // if off screen left
			ship.setX((float)GAME_WIDTH);      // position off screen right
		ship.setDegrees(ship.getDegrees() + frameTime * ROTATION_RATE * -1);

		if (ship2.getX() > GAME_WIDTH)               // if off screen right
			ship2.setX((float)-ship2.getWidth());  // position off screen left
		ship2.setDegrees(ship2.getDegrees() + frameTime * ROTATION_RATE2 * -1);
	}

	if (input->isKeyDown(SHIP_UP_KEY))               // if move up
	{
		ship.setY(ship.getY() - frameTime * SHIP_SPEED);
		if (ship.getY() < -ship.getHeight())        // if off screen top
			ship.setY((float)GAME_HEIGHT);     // position off screen bottom
	}

	if (input->isKeyDown(SHIP_DOWN_KEY))             // if move down
	{
		ship.setY(ship.getY() + frameTime * SHIP_SPEED);
		if (ship.getY() > GAME_HEIGHT)              // if off screen bottom
			ship.setY((float)-ship.getHeight());    // position off screen top
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

	nebula.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	ship.draw();
	ship2.draw();

	graphics->spriteEnd();                  // end drawing sprites
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	planetTexture.onLostDevice();
	nebulaTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	nebulaTexture.onResetDevice();
	planetTexture.onResetDevice();

    Game::resetAll();
    return;
}



