#include "spaceWar.h"
#include <vector>
using namespace std;
float time = 0.0f;
bool status = false;

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

//=============================================================================
// Rocket
//=============================================================================
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

//=============================================================================
// Misc Background Stuff
//=============================================================================
	// main game textures
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// farback texture
	if (!farbackTexture.initialize(graphics, FARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback texture"));

	// farback image
	if (!farback.initialize(graphics,0,0,0,&farbackTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback"));

//=============================================================================
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	// enemy bullet texture
	if (!ebulletTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing enemy bullet texture"));

	// enemy bullet
	if (!ebullet.initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy bullet"));
	ebullet.setX(GAME_WIDTH / 4);
	ebullet.setX(GAME_HEIGHT / 4);

//=============================================================================
// Enemy Ship 
//=============================================================================
	// enemy ship texture
	if (!eShipTexture.initialize(graphics, ESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy ship texture"));

	// enemy ship
	if (!eShip.initialize(this, eShipNS::WIDTH, eShipNS::HEIGHT, eShipNS::TEXTURE_COLS, &eShipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy ship"));
	eShip.setFrames(eShipNS::ESHIP1_START_FRAME, eShipNS::ESHIP1_END_FRAME);
	eShip.setCurrentFrame(eShipNS::ESHIP1_START_FRAME);
	
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
			waitTimer = 0.2f;
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

	//Potential Bullet Aiming Code
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

//=============================================================================
// Update frameTime for Animation 
//=============================================================================
	rocketMain.update(frameTime);

	for each(Bullet*  bull in bulletList)
	{
		bull->update(frameTime);
	}

	for each (EBullet* b in ebulletList)
	{
		b->update(frameTime);
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
 
	for each(Bullet*  bull in bulletList)
	{
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
	}

	for each (EBullet* b in ebulletList)
	{
		if (rocketMain.collidesWith(*b, collisionVector))
		{
			rocketMain.bounce(collisionVector, *b);
			b->setActive(false);
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	farback.draw();							// add the farback to the scene

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
		if (b->getActive() == true)
		{
			if (b != NULL)
				if (status == true)
					status = true;
				b->draw();
		}		
	}

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
