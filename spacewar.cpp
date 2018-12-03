// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include <vector>
using namespace std;
float time = 0.0f;
bool status = false;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	/*
	dxFontSmall = new TextDX();     // DirectX fonts
	dxFontMedium = new TextDX();
	dxFontLarge = new TextDX();
	*/
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
	/*
	SAFE_DELETE(dxFontSmall);
	SAFE_DELETE(dxFontMedium);
	SAFE_DELETE(dxFontLarge);
	*/
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
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
	
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	/*
	// bullet
	if (!bullet.initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet"));
	bullet.setX(0);
	bullet.setY(0);
	*/

	// enemy ship texture
	if (!eShipTexture.initialize(graphics, ESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy ship texture"));

	// enemy ship
	if (!eShip.initialize(this, eShipNS::WIDTH, eShipNS::HEIGHT, eShipNS::TEXTURE_COLS, &eShipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy ship"));
	eShip.setFrames(eShipNS::ESHIP1_START_FRAME, eShipNS::ESHIP1_END_FRAME);
	eShip.setCurrentFrame(eShipNS::ESHIP1_START_FRAME);

	// enemy bullet texture
	if (!ebulletTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing enemy bullet texture"));

	// enemy bullet
	if (!ebullet.initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy bullet"));
	ebullet.setX(GAME_WIDTH / 4);
	ebullet.setX(GAME_HEIGHT / 4);

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
	waitTimer -= frameTime;
	time -= frameTime;
	if (waitTimer <= 0.0f)
	{
		if (input->wasKeyPressed(ROCKET_SPACE_KEY) == true)
		{
			waitTimer = 0.4f;
			Bullet *b = new Bullet();
			b->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
			bulletList.push_back(b);
			b->shoot(&rocketMain);
			input->clearKeyPress(ROCKET_SPACE_KEY);
		}
	}
	
	if (time <= 0.0f) {
		if (eshipList.size() < 6)
		{
			EShip *e = new EShip();
			e->initialize(this, eShipNS::WIDTH, eShipNS::HEIGHT, eShipNS::TEXTURE_COLS, &eShipTexture);
			e->setX(GAME_WIDTH - eShipNS::WIDTH);
			e->setY(rand() & GAME_HEIGHT);
			eshipList.push_back(e);
			time = 2.0f;
		}
		
	}

	for each (EShip* e in eshipList)
	{
		e->update(frameTime);
		if (e->shotTimer <= 0.0f)
		{
			EBullet* b = new EBullet;
			b->initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebulletTexture);
			ebulletList.push_back(b);
			b->getDir(e);
			e->shotTimer = 1.0f;
		}
	}
	for each (EBullet* b in ebulletList)
	{
		b->update(frameTime);
	}
	ebullet.update(frameTime);
	
	/*
	for each (EBullet* b in ebulletList)
	{
		if (b->getX() < 0)
		{
			SAFE_DELETE(b);
			ebulletList.erase();
			status = true;
		}
	}
	*/
    planet.update(frameTime);
    ship1.update(frameTime);
    ship2.update(frameTime);
	rocketMain.update(frameTime);
	for each(Bullet*  bull in bulletList)
	{
		bull->update(frameTime);
	}

	//bulletTemp.update(frameTime);
	/*
	VECTOR2 bulletVector = bullet.getCenter();
	VECTOR2 rocketVector = rocketMain.getCenter();
	//const VECTOR2* bulletVector = bullet.getCenter();
	//const VECTOR2* rocketVector = rocketMain.getCenter();

	VECTOR2 chase = rocketVector - bulletVector;
	Graphics::Vector2Normalize(&chase);
	bullet.setX(chase.x * frameTime);
	bullet.setY(chase.y * frameTime);
	*/
	if (planet.getHealth() <= 0)
	{
		planet.setActive(false);        
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

	for each(Bullet*  bull in bulletList)
	{
		if (bull->collidesWith(planet, collisionVector))
		{
			// bounce off planet
			bull->bounce(collisionVector, planet);
			bull->isFired = false;
			planet.setHealth(planet.getHealth() - 100);
			bull->setActive(false);
		}

		for each (EShip* eshat in eshipList)
		{
			if (bull->collidesWith(*eshat, collisionVector))
			{
				// bounce off planet
				bull->bounce(collisionVector, *eshat);
				bull->isFired = false;
				eshat->setHealth(eshat->getHealth() - 100);
				bull->setActive(false);
			}
		}
		
	/*
	if (bullet.collidesWith(ship1, collisionVector))
	{
		// bounce off ship
		bullet.bounce(collisionVector, ship1);
		//bullet.damage(SHIP);
		// change the direction of the collisionVector for ship1
		//ship1.bounce(collisionVector*-1, bullet);
		ship1.damage(SHIP);
	}
	if (bullet.collidesWith(ship2, collisionVector))
	{
		// bounce off ship
		bullet.bounce(collisionVector, ship2);
		//bullet.damage(SHIP);
		// change the direction of the collisionVector for ship1
		//ship1.bounce(collisionVector*-1, bullet);
		ship2.damage(SHIP);
	}	
	*/
	}
	
	
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
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites
	farback.draw();							// add the farback to the scene
	if (planet.getHealth() > 0)
	{
		planet.draw();                          // add the planet to the scene	
	}
	
    //ship1.draw();                           // add the spaceship to the scene
    //ship2.draw();                           // add the spaceship to the scene
	rocketMain.draw();						// add the rocket to the scene

	for each(Bullet*  bull in bulletList)
	{
		bull->draw();
	}
	for each(EShip*  enemy in eshipList)	// all eship draw functions go here
	{
		if (enemy->getHealth() > 0)
			enemy->draw();						// draw every enemy ship in the list
		else
			enemy->setActive(false);
	}
	
	for each (EBullet* b in ebulletList)
	{
		if (b != NULL)
			if (status == true)
				status = true;
			b->draw();	
	}
	//bullet.draw();
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    gameTextures.onLostDevice();
	farbackTexture.onLostDevice();
	rocketTexture.onLostDevice();
	bulletTexture.onLostDevice();
	eShipTexture.onLostDevice();
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
	rocketTexture.onResetDevice();
	farbackTexture.onResetDevice();
	bulletTexture.onResetDevice();
	eShipTexture.onResetDevice();
    Game::resetAll();
    return;
}
