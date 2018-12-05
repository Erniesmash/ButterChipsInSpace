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
// Powerups
//=============================================================================
	// powerup texture
	if (!powerupTexture.initialize(graphics, POWERUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup texture"));

	// speed boost texture
	if (!sbTexture.initialize(graphics, SPEEDBOOST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup texture"));

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

	// starfield texture
	if (!starfieldTexture.initialize(graphics, STARFIELD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield texture"));

	// starfield image
	if (!starfield.initialize(graphics, 0, 0, 0, &starfieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield"));

//=============================================================================
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	// enemy bullet texture
	if (!ebulletTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing enemy bullet texture"));

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
	//checkEShip();
	waitTimer -= frameTime;
	sbSpawnTime -= frameTime;
	time -= frameTime;
	bulletSpeedTime -= frameTime;

	if (rocketMain.getbulletSpeedActivated() == false)
	{
		if (waitTimer <= 0.0f)
		{
			if (input->isKeyDown(ROCKET_SPACE_KEY) == true)
			{
				waitTimer = 0.8f;
				Bullet *b = new Bullet();
				b->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
				bulletList.push_back(b);
				b->shoot(&rocketMain, frameTime);
				input->clearKeyPress(ROCKET_SPACE_KEY);
			}
		}
	}

	if (rocketMain.getbulletSpeedActivated() == true)
	{
		if (waitTimer <= 0.0f)
		{
			if (input->isKeyDown(ROCKET_SPACE_KEY) == true)
			{
				waitTimer = 0.06f;
				Bullet *b = new Bullet();
				b->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
				bulletList.push_back(b);

				for each (Bullet* b in bulletList)
				{
					b->increaseSpeed = true;
				}
				b->shoot(&rocketMain, frameTime);
				//b->setScale(10);
				//b->shoot(&rocketMain, frameTime);
				input->clearKeyPress(ROCKET_SPACE_KEY);
			}
		}
	}

	if (time <= 0.0f) {
		if (eshipList.size() < 6)
		{
			EShip *e = new EShip();
			e->initialize(this, eShipNS::WIDTH, eShipNS::HEIGHT, eShipNS::TEXTURE_COLS, &eShipTexture);
			e->setX(GAME_WIDTH - eShipNS::WIDTH);
			e->setY(rand() % (GAME_HEIGHT - eShipNS::HEIGHT));
			eshipList.push_back(e);
			time = 2.0f;
		}

	}

	if (bulletSpeedTime <= 0.0f)
	{
		if (bulletSpeedPowerupList.size() <= 3)
		{
			Powerup *speedBoost = new Powerup();
			speedBoost->initialize(this, powerupNS::WIDTH, powerupNS::HEIGHT, powerupNS::TEXTURE_COLS, &powerupTexture);
			speedBoost->setX(rand() % (GAME_WIDTH - powerupNS::WIDTH));
			speedBoost->setY(rand() % (GAME_HEIGHT - powerupNS::HEIGHT));
			speedBoost->setVelocity(VECTOR2(-powerupNS::SPEED, -powerupNS::SPEED));
			bulletSpeedPowerupList.push_back(speedBoost);
			bulletSpeedTime = 15.0f;
		}
	}

	if (sbSpawnTime <= 0.0f)
	{
		if (sbList.size() <= 2)
		{
			SpeedBoost *sb = new SpeedBoost();
			sb->initialize(this, speedboostNS::WIDTH, speedboostNS::HEIGHT, speedboostNS::TEXTURE_COLS, &sbTexture);
			sb->setX(rand() % (GAME_WIDTH - speedboostNS::WIDTH));
			sb->setY(rand() % (GAME_HEIGHT - speedboostNS::HEIGHT));
			sbList.push_back(sb);
			sbSpawnTime = 60.0f;
		}
	}

	for each (EShip* e in eshipList)
	{
		e->update(frameTime);
		e->chase(&rocketMain);
		if (e->shotTimer <= 0.0f)
		{
			EBullet* b = new EBullet;
			b->initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebulletTexture);
			e->ebulletList.push_back(b);
			b->getDir(&rocketMain, e);
			e->shotTimer = 1.0f;
		}
		for each (EBullet* b in e->ebulletList)
		{
			b->update(frameTime);
		}
	}	
	
	// delete vector items
	checkEShip();
	checkSB();
	checkEB();
	for (vector<Powerup*>::iterator it = bulletSpeedPowerupList.begin();
		it != bulletSpeedPowerupList.end();)
	{
		if ((*it)->getActive() == false)
		{
			SAFE_DELETE(*it);
			it = bulletSpeedPowerupList.erase(it);
		}
		else
		{
			++it;
		}
	}

//=============================================================================
// Update frameTime for Animation 
//=============================================================================
	rocketMain.update(frameTime);

	for each(Bullet*  bull in bulletList)
	{
		bull->update(frameTime);
	}

	
	for each (Powerup* p in bulletSpeedPowerupList)
	{
		p->update(frameTime);
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
				eshat->checkCollided = true;
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

	for each (Powerup* p in bulletSpeedPowerupList)
	{
		if (rocketMain.collidesWith(*p, collisionVector))
		{
			rocketMain.bounce(collisionVector, *p);
			p->setActive(false);
			rocketMain.setbulletSpeedActivated(true);
		}
	}

	for each (SpeedBoost* sb in sbList)
	{
		if (sb->collidesWith(rocketMain, collisionVector))
		{
			sb->collided = true;
			rocketMain.sbActive = true;
		}
	}

	for each (EShip* e in eshipList)
	{
		if (e->collidesWith(rocketMain, collisionVector))
		{
			e->setVelocity(-(e->getVelocity()));
			e->checkCollided = true;
		}

		if (e->collidesWith(*e, collisionVector))
		{
			e->bounce(collisionVector, *e);
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

	starfield.draw();

	for each (Powerup* p in bulletSpeedPowerupList)
	{
		if (p != NULL && p->getActive() == true)
		{
			p->draw();
		}
	}
	
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

		for each (EBullet* b in enemy->ebulletList)
		{
			if (b != NULL)
			{
				if (status == true)
					status = true;
				b->draw();
			}
		}
	}

	for each(SpeedBoost* sb in sbList)
	{
		if (sb != NULL)
		{
			sb->draw();
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
	starfieldTexture.onLostDevice();
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
	starfieldTexture.onResetDevice();
	bulletTexture.onResetDevice();
	eShipTexture.onResetDevice();
    Game::resetAll();
    return;
}

void Spacewar::checkEShip()
{
	for (vector<EShip*>::iterator it = eshipList.begin();
		it != eshipList.end();)
	{
		if ((*it)->checkCollided)
		{
			SAFE_DELETE(*it);
			it = eshipList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Spacewar::checkSB()
{
	for (vector<SpeedBoost*>::iterator it = sbList.begin();
		it != sbList.end();)
	{
		if ((*it)->collided)
		{
			SAFE_DELETE(*it);
			it = sbList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Spacewar::checkEB()
{
	for each (EShip* e in eshipList)
	{
		for (vector<EBullet*>::iterator it = e->ebulletList.begin();
			it != e->ebulletList.end();)
		{
			if ((*it)->collided)
			{
				SAFE_DELETE(*it);
				it = e->ebulletList.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}
/*
void Spacewar::checkBullet()
{
	for (vector<Bullet*>::iterator it = bulletList.begin();
		it != bulletList.end();)
	{
		if ((*it)->checkCollided)
		{
			SAFE_DELETE(*it);
			it = bulletList.erase(it);
		}
		else
		{
			++it;
		}
	}
}
*/
