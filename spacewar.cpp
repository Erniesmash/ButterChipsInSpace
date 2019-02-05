//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "spaceWar.h"
#include <vector>
using namespace std;
float time = 0.0f;
bool status = false;
float gg = 100;

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
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	// enemy bullet texture
	if (!ebulletTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing enemy bullet texture"));

//=============================================================================
// Player
//=============================================================================
	// player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));

	// player
	if (!playerMain.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));


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
// Enemy Ship 
//=============================================================================
	// enemy ship texture
	if (!eShipTexture.initialize(graphics, ESHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy ship texture"));
	
//=============================================================================
// BAKURETSU MAHOU
//=============================================================================
	if (!explosionTexture.initialize(graphics, EXPLOSION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing explosion"));

//=============================================================================
// Enemies
//=============================================================================
	if (!dfrTexture.initialize(graphics, DFR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfr"));
	if (!dfbTexture.initialize(graphics, DFB_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfb"));
	if (!dfgTexture.initialize(graphics, DFG_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing dfg"));
	if (!skullTexture.initialize(graphics, SKULL_ENTRANCE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing skull"));
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing boss"));
	if (!ebTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing eb"));

	//spawn enemies on game start
	spawnBoss(GAME_WIDTH - bossNS::WIDTH*3, GAME_HEIGHT / 2);
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	playerMain.update(frameTime);
	time -= frameTime;

	for each (Dfr* r in dfrList)
	{
		r->getPlayer(&playerMain);
		r->update(frameTime);

		if (r->dead == true && r->imgChanged == false)
		{
			dfrTexture.initialize(graphics, DF_DEATH_IMAGE);
			r->setCurrentFrame(dfrNS::DFR_START_FRAME);
			r->imgChanged = true;
		}
	}

	for each (Dfb* b in dfbList)
	{
		b->update(frameTime);
		if (b->dead == true && b->imgChanged == false)
		{
			dfbTexture.initialize(graphics, DF_DEATH_IMAGE);
			b->setCurrentFrame(dfbNS::DFB_START_FRAME);
			b->imgChanged = true;
		}
	}
	
	for each (Dfg* g in dfgList)
	{
		g->update(frameTime);
		if (g->dead == true && g->imgChanged == false)
		{
			dfgTexture.initialize(graphics, DF_DEATH_IMAGE);
			g->setCurrentFrame(dfgNS::DFG_START_FRAME);
			g->imgChanged = true;
		}
	}

	for each (Skull* skull in skullList)
	{
		skull->update(frameTime);
		skull->getPlayer(&playerMain);

		//skull appear
		if (skull->getCurrentFrame() == skullNS::SKULL_END_FRAME)
		{
			skull->setCurrentFrame(skullNS::ACTIVE_END_FRAME);
			skull->enteredChanged = true;
		}
		
		if (skull->entered == true && skull->enteredChanged == true && skull->active == false)
		{
			skull->setCurrentFrame(skullNS::ACTIVE_END_FRAME);
			skullTexture.initialize(graphics, SKULL_IMAGE);
			skull->active = true;
		}

		if (skull->exited == true)
		{
			for (int i = 1; i < 25; i++)
			{
				ebTexture.initialize(graphics, EBULLET_IMAGE);
				EBullet* e = new EBullet;
				e->initialize(this, ebulletNS::WIDTH, ebulletNS::HEIGHT, ebulletNS::TEXTURE_COLS, &ebTexture);
				e->appImpulse(skull->getCenterX(), skull->getCenterY(), 0 + 15 * i, 30);
				ebList.push_back(e);
			}
		}
	}

	for each (Boss* boss in bossList)
	{
		boss->update(frameTime);
	}

	for each  (EBullet* eb in ebList)
	{
		eb->update(frameTime);
	}

	if (time <= 0)
	{
		spawnSkull(GAME_WIDTH - bossNS::WIDTH * 3, rand() % (GAME_HEIGHT - skullNS::HEIGHT));
		time = 1.0f;
	}

	// check to delete vector items
	checkDfr();
	checkDfb();
	checkDfg();
	checkSkull();
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

		for each (EBullet* b in e->ebulletList)
		{
			if (rocketMain.collidesWith(*b, collisionVector))
			{
				rocketMain.setHealth(rocketMain.getHealth() - 100);
				rocketMain.bounce(collisionVector, *b);
				b->collided = true;
			}
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

	playerMain.draw();

	for each (Dfr* d in dfrList)
	{
		d->draw();
	}
	for each (Dfb* b in dfbList)
	{
		b->draw();
	}

	for each (Dfg* g in dfgList)
	{
		g->draw();
	}

	for each (Skull* skull in skullList)
	{
		skull->draw();
	}

	for each (Boss* boss in bossList)
	{
		boss->draw();
	}

	for each (EBullet* eb in ebList)
	{
		eb->draw();
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

void Spacewar::checkDfr()
{
	for (vector<Dfr*>::iterator it = dfrList.begin();
		it != dfrList.end();)
	{
		if ((*it)->dead == true && (*it)->imgChanged == true && (*it)->getCurrentFrame() == 6)
		{
			SAFE_DELETE(*it);
			it = dfrList.erase(it);
		}

		else if (rocketMain.getActive() == false)
		{
			SAFE_DELETE(*it);
			it = dfrList.erase(it);
		}

		else
		{
			++it;
		}
	}
}

void Spacewar::checkDfb()
{
	for (vector<Dfb*>::iterator it = dfbList.begin();
		it != dfbList.end();)
	{
		if ((*it)->dead == true && (*it)->imgChanged == true && (*it)->getCurrentFrame() == 6)
		{
			SAFE_DELETE(*it);
			it = dfbList.erase(it);
		}

		else if (rocketMain.getActive() == false)
		{
			SAFE_DELETE(*it);
			it = dfbList.erase(it);
		}

		else
		{
			++it;
		}
	}
}

void Spacewar::checkDfg()
{
	for (vector<Dfg*>::iterator it = dfgList.begin();
		it != dfgList.end();)
	{
		if ((*it)->dead == true && (*it)->imgChanged == true && (*it)->getCurrentFrame() == 6)
		{
			SAFE_DELETE(*it);
			it = dfgList.erase(it);
		}

		else if (rocketMain.getActive() == false)
		{
			SAFE_DELETE(*it);
			it = dfgList.erase(it);
		}

		else
		{
			++it;
		}
	}
}

void Spacewar::checkSkull()
{
	for (vector<Skull*>::iterator it = skullList.begin();
		it != skullList.end();)
	{
		if ((*it)->dead == true)
		{
			SAFE_DELETE(*it);
			it = skullList.erase(it);
		}

		if ((*it)->exited == true)
		{
			SAFE_DELETE(*it);
			it = skullList.erase(it);
		}

		else
		{
			++it;
		}
	}
}

void Spacewar::checkBoss()
{
	/*for (vector<Dfr*>::iterator it = dfrList.begin();
		it != dfrList.end();)
	{
		if ((*it)->dead == true && (*it)->imgChanged == true && (*it)->getCurrentFrame() == 6)
		{
			SAFE_DELETE(*it);
			it = dfrList.erase(it);
		}

		else if (rocketMain.getActive() == false)
		{
			SAFE_DELETE(*it);
			it = dfrList.erase(it);
		}

		else
		{
			++it;
		}
	}*/
}
