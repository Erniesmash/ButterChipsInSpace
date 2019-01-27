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

	// dxFont
	if (dxFont.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));

	// dxFont Green
	if (dxFontGreen.initialize(graphics, gameNS::POINT_SIZE, false, false, gameNS::FONT) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize DirectX font."));
	dxFontGreen.setFontColor(spacewarNS::FONT_COLOR);

	// initialize DirectX fonts
	fontBig.initialize(graphics, spacewarNS::FONT_BIG_SIZE, false, false, spacewarNS::FONT);

	// heart texture
	if (!heartTexture.initialize(graphics, HEART_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing heart texture"));

	for (int x = 0; x < numberOfLives; x++)
	{
		Heart *heart = new Heart();
		heart->initialize(this, heartNS::WIDTH, heartNS::HEIGHT, heartNS::TEXTURE_COLS, &heartTexture);
		heart->setX(GAME_WIDTH / 24 * (numberOfLives - (x - 17.5)));
		heart->setY(GAME_HEIGHT / 100);
		heartList.push_back(heart);
	}

	// selection texture
	if (!selectionTexture.initialize(graphics, SELECTION_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing selection texture"));

	// selection items
	for (int x = 0; x < numberOfSpecials; x++)
	{
		Selection *selection = new Selection();
		selection->initialize(this, selectionNS::WIDTH, selectionNS::HEIGHT, selectionNS::TEXTURE_COLS, &selectionTexture);
		selection->setX(GAME_WIDTH / 15 * (numberOfSpecials - (x + 0.8)));
		selection->setY(GAME_HEIGHT / 100);
		selectionList.push_back(selection);
	}

	// specials texture
	if (!specialsTexture.initialize(graphics, SPECIALS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing specials texture"));

	// specials items
	for (int x = 0; x < numberOfSpecials; x++)
	{
		Specials *special = new Specials();
		special->initialize(this, specialsNS::WIDTH, specialsNS::HEIGHT, specialsNS::TEXTURE_COLS, &specialsTexture);
		//special->setFrames(x, x);
		special->setCurrentFrame(x);
		special->setX(GAME_WIDTH / 15 * (numberOfSpecials - (x + 0.8)));
		special->setY(GAME_HEIGHT / 100);
		specialList.push_back(special);
	}

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
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	// enemy bullet texture
	if (!ebulletTexture.initialize(graphics, EBULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error intializing enemy bullet texture"));



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
	/*
//=============================================================================
// Powerups
//=============================================================================
	// powerup texture
	if (!powerupTexture.initialize(graphics, POWERUP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup texture"));

	// speed boost texture
	if (!sbTexture.initialize(graphics, SPEEDBOOST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup texture"));
		*/

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
}
	
//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//checkEShip();
	waitTimer -= frameTime;
	sbSpawnTime -= frameTime;	//spawn timer for speed boost
	time -= frameTime;			//spawn timer for enemy
	bulletSpeedTime -= frameTime;


	// run the update for explosions
	for each (Explosion* ex in explosionList)
	{
		ex->update(frameTime);
	}

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

	// spawns a ship
	if (time <= 0.0f) {
		EShip *e = new EShip();
		e->initialize(this, eShipNS::WIDTH, eShipNS::HEIGHT, eShipNS::TEXTURE_COLS, &eShipTexture);
		e->setX(GAME_WIDTH - eShipNS::WIDTH);
		e->setY(rand() % (GAME_HEIGHT - eShipNS::HEIGHT));
		eshipList.push_back(e);
		time = 1.0f;
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

	// spawns a speed boost
	if (sbSpawnTime <= 0.0f)
	{
		if (sbList.size() <= 2)
		{
			SpeedBoost *sb = new SpeedBoost();
			sb->initialize(this, speedboostNS::WIDTH, speedboostNS::HEIGHT, speedboostNS::TEXTURE_COLS, &sbTexture);
			sb->setX(rand() % (GAME_WIDTH - speedboostNS::WIDTH));
			sb->setY(rand() % (GAME_HEIGHT - speedboostNS::HEIGHT));
			sbList.push_back(sb);
			sbSpawnTime = 30.0f;
		}
	}

	// run eship update function and ebullet update function inside the eships ebullet list
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
	
	// check to delete vector items
	checkEShip();
	checkSB();
	checkEB();
	checkEx();

	if (rocketMain.getHealth() <= 0)
	{
		rocketMain.setActive(false);
		for (vector<Bullet*>::iterator it = bulletList.begin();
			it != bulletList.end();)
		{
			SAFE_DELETE(*it);
			it = bulletList.erase(it);
		}
		for each (EShip* e in eshipList)
		{
			e->checkCollided = true;
			for each (EBullet* eb in e->ebulletList)
			{
				eb->collided = true;
			}
		}
	}
	
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

	playerMain.update(frameTime);
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

				Explosion *ex = new Explosion;
				ex->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
				ex->setX((eshat)->getX());
				ex->setY((eshat)->getY());
				ex->setScale(0.4);
				explosionList.push_back(ex);
			}
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

	if (heartList.size() != 0)
	{
		for each (Heart* h in heartList)
		{
			if (h->getActive() == true)
			{
				h->draw();
			}
		}
	}

	for each (Selection* s in selectionList)
	{
		if (s->getActive() == true)
		{
			s->draw();
		}
	}

	for each (Specials* s in specialList)
	{
		if (s->getActive() == true)
		{
			s->draw();
		}
	}

	/*
	_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Welcome to ブロブとトラブル");
	dxFont.print(buffer, GAME_WIDTH/100, GAME_HEIGHT/1.05);
	*/

	_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Click 1, 2, 3 or 4 to use Special Abilities!");
	dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);

	//Ability One Dash
	if (playerMain.dashOnCooldown == true)
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)playerMain.dashCooldownTimer);
		dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
	}

	else
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
		dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
	}

	//Ability Two
	_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
	dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);

	//Ability Three
	_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
	dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);

	//Ability Four
	_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
	dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);

	//change ability/specials selection
	if (input->isKeyDown(ONE_KEY))
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
		fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
	}

	if (input->isKeyDown(TWO_KEY))
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
		fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
		
	}

	if (input->isKeyDown(THREE_KEY))
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
		fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
	}

	if (input->isKeyDown(FOUR_KEY))
	{
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
		fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
	}

	for each (Powerup* p in bulletSpeedPowerupList)
	{
		if (p != NULL && p->getActive() == true)
		{
			p->draw();
		}
	}
	for each (Explosion* ex in explosionList)
	{
		if (ex != NULL)
		{
			ex->draw();
		}
	}
	if (rocketMain.getHealth() > 0)
	{
		rocketMain.draw();						// add the rocket to the scene
	}

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
	heartTexture.onLostDevice();
	specialsTexture.onLostDevice();
	selectionTexture.onLostDevice();
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
	heartTexture.onResetDevice();
	specialsTexture.onResetDevice();
	selectionTexture.onResetDevice();
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
			Explosion *ex = new Explosion;
			ex->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
			ex->setX((*it)->getX());
			ex->setY((*it)->getY());
			explosionList.push_back(ex);
			SAFE_DELETE(*it);
			it = eshipList.erase(it);
		}

		else if (rocketMain.getActive() == false)
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
				Explosion *ex = new Explosion;
				ex->initialize(this, explosionNS::WIDTH, explosionNS::HEIGHT, explosionNS::TEXTURE_COLS, &explosionTexture);
				ex->setX((*it)->getX());
				ex->setY((*it)->getY());
				ex->setScale(0.4);
				explosionList.push_back(ex);
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

void Spacewar::checkEx()
{
	for (vector<Explosion*>::iterator it = explosionList.begin();
		it != explosionList.end();)
	{
		if ((*it)->exploded)
		{
			SAFE_DELETE(*it);
			it = explosionList.erase(it);
		}
		else
		{
			++it;
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
