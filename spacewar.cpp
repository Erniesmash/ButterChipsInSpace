// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

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
	/*
    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
	
    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
	*/

	// main game textures
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	// farback texture
	if (!farbackTexture.initialize(graphics, FARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback texture"));

	// farback image
	if (!farback.initialize(graphics,0,0,0,&farbackTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback"));

	// rocket texture
	if (!rocketTexture.initialize(graphics, ROCKET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket texture"));

	// rocket
	if (!rocketMain.initialize(this, rocketNS::WIDTH, rocketNS::HEIGHT, rocketNS::TEXTURE_COLS, &rocketTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket"));
	rocketMain.setFrames(rocketNS::ROCKET_START_FRAME, rocketNS::ROCKET_END_FRAME);
	rocketMain.setCurrentFrame(rocketNS::ROCKET_START_FRAME);
	rocketMain.setX(GAME_WIDTH / 2.3);
	rocketMain.setY(GAME_HEIGHT / 1.15);
	//rocketMain.setVelocity(VECTOR2(1,1)); // VECTOR2(X, Y)

	// ship1
	if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX(GAME_WIDTH/4);
    ship1.setY(GAME_HEIGHT/4);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)

    // ship2
    if (!ship2.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship2"));
    ship2.setFrames(shipNS::SHIP2_START_FRAME, shipNS::SHIP2_END_FRAME);
    ship2.setCurrentFrame(shipNS::SHIP2_START_FRAME);
    ship2.setX(GAME_WIDTH - GAME_WIDTH/4);
    ship2.setY(GAME_HEIGHT/4);
    ship2.setVelocity(VECTOR2(-shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
    planet.update(frameTime);
    ship1.update(frameTime);
    ship2.update(frameTime);
	rocketMain.update(frameTime);
	/*
	if (input->isKeyDown(ROCKET_RIGHT_KEY))            // if move right
	{
		//if (rocketMain.getX() < GAME_WIDTH - rocketMain.getWidth())
		rocketMain.setX(rocketMain.getX() + frameTime * rocketNS::SPEED);
	}

	if (input->isKeyDown(ROCKET_LEFT_KEY))             // if move left
	{
		//if (rocketMain.getX() > 0)
		rocketMain.setX(rocketMain.getX() - frameTime * rocketNS::SPEED);
	}

	if (input->isKeyDown(ROCKET_UP_KEY))               // if move up
	{
		//if (rocketMain.getY() > 0 + rocketMain.getHeight()) // limit move up
		rocketMain.setY(rocketMain.getY() - frameTime * rocketNS::SPEED);
	}

	if (input->isKeyDown(ROCKET_DOWN_KEY))             // if move down
	{
		//if (rocketMain.getY() < GAME_HEIGHT - rocketMain.getHeight()) // limit move down
		rocketMain.setY(rocketMain.getY() + frameTime * rocketNS::SPEED);
	}
	*/
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
{
    VECTOR2 collisionVector;
    // if collision between ship and planet
    if(ship1.collidesWith(planet, collisionVector))
    {
        // bounce off planet
        ship1.bounce(collisionVector, planet);
        ship1.damage(PLANET);
    }
    if(ship2.collidesWith(planet, collisionVector))
    {
        // bounce off planet
        ship2.bounce(collisionVector, planet);
        ship2.damage(PLANET);
    }
    // if collision between ships
    if(ship1.collidesWith(ship2, collisionVector))
    {
        // bounce off ship
        ship1.bounce(collisionVector, ship2);
        ship1.damage(SHIP);
        // change the direction of the collisionVector for ship2
        ship2.bounce(collisionVector*-1, ship1);
        ship2.damage(SHIP);
    }
	/*
	if (rocketMain.collidesWith(planet, collisionVector))
	{
		rocketMain.bounce(collisionVector, planet);
		rocketMain.damage(PLANET);
	}
	if (rocketMain.collidesWith(ship1, collisionVector))
	{
		// bounce off ship
		rocketMain.bounce(collisionVector, ship1);
		rocketMain.damage(SHIP);
		// change the direction of the collisionVector for ship2
		ship1.bounce(collisionVector*-1, rocketMain);
		ship1.damage(SHIP);
	}
	*/
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    //nebula.draw();                          // add the orion nebula to the scene
	farback.draw();							// add the farback to the scene
    planet.draw();                          // add the planet to the scene
    ship1.draw();                           // add the spaceship to the scene
    ship2.draw();                           // add the spaceship to the scene
	rocketMain.draw();						// add the rocket to the scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    //nebulaTexture.onLostDevice();
    gameTextures.onLostDevice();
	farbackTexture.onLostDevice();
	rocketTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    //nebulaTexture.onResetDevice();
	rocketTexture.onResetDevice();
	farbackTexture.onResetDevice();
    Game::resetAll();
    return;
}
