#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	menuOn = true;
}

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

	// initialize DirectX fonts
	fontMenu.initialize(graphics, spacewarNS::FONT_MENU_SIZE, false, false, spacewarNS::FONT_MENU);

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
	playerMain.setX(GAME_WIDTH / 3);

	// player menu
	if (!startPlayer.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing startplayer"));

//=============================================================================
// Missle
//=============================================================================
	// missle texture
	if (!missleTexture.initialize(graphics, MISSLE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missle texture"));

	// missle
	if (!missleShot.initialize(this, missleNS::WIDTH, missleNS::HEIGHT, missleNS::TEXTURE_COLS, &missleTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missle"));

//=============================================================================
// Bullet Stuff
//=============================================================================
	// bullet texture
	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

//=============================================================================
// Misc Background Stuff
//=============================================================================
	// main game textures
	if (!gameTextures.initialize(graphics, TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// farback texture
	if (!farbackTexture.initialize(graphics, FARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing farback texture"));

	// space texture
	if (!spaceTexture.initialize(graphics, SPACE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space texture"));

	// farback image
	if (!space.initialize(graphics,0,0,0,&spaceTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing space"));

	// starfield texture
	if (!starfieldTexture.initialize(graphics, STARFIELD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield texture"));

	// starfield image
	if (!starfield.initialize(graphics, 0, 0, 0, &starfieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing starfield"));

	// menu image
	if (!menu.initialize(graphics, 0, 0, 0, &farbackTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	PlaySound("C:\\Users\\ernes\\Documents\\GitHub\\ButterChipsInSpace\\audio\\menu.wav", NULL, SND_LOOP | SND_ASYNC);
}
	
//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	waitTimer -= frameTime;
	if (menuOn == true)
	{
		if (input->anyKeyPressed())
		{
			menuOn = false;
			input->clearAll();
		}

		startPlayer.setX(startPlayer.getX() + frameTime * playerNS::SPEED);
		startPlayer.update(frameTime);

		if (startPlayer.getX() > GAME_WIDTH - playerNS::WIDTH * startPlayer.getScale() - 1)    // if hit right screen edge
		{
			startPlayer.setX(0);    // position at right screen edge
		}
	}
	
	if (menuOn == false)
	{
		for (std::vector<Bullet*>::iterator it = bulletList.begin();
			it != bulletList.end();)
		{
			if ((*it)->bounceInUseTimer == 4)
			{
				if ((*it)->getX() > GAME_WIDTH - bulletNS::WIDTH * (*it)->getScale())    // if hit right screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}
				else if ((*it)->getX() < 0)                    // else if hit left screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}

				else if ((*it)->getY() > GAME_HEIGHT - bulletNS::HEIGHT * (*it)->getScale())  // if hit bottom screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}
				else if ((*it)->getY() < 0)                    // else if hit top screen edge
				{
					SAFE_DELETE(*it);
					it = bulletList.erase(it);
				}

				else
				{
					++it;
				}
			}

			else
			{
				++it;
			}
		}

		if (missleShot.missleActive == false)
		{
			if (input->isKeyDown(THREE_KEY))
			{
				missleShot.shoot(&playerMain, frameTime);
				missleShot.missleActive = true;
			}
		}

		if (input->getMouseLButton() == true)
		{
			if (waitTimer <= 0.0f)
			{
				waitTimer = 0.4f;
				Bullet *b = new Bullet();
				b->initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture);
				bulletList.push_back(b);
				b->shoot(&playerMain, frameTime);
				audio->playCue(GUNSHOT1);
			}
		}

		//=============================================================================
		// Update frameTime for Animation 
		//=============================================================================

		for each(Bullet*  bull in bulletList)
		{
			bull->update(frameTime);
		}

		playerMain.update(frameTime);
		missleShot.update(frameTime);
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
	if (menuOn == false)
	{
	}    
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	if (menuOn == true)
	{
		menu.draw();
		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Blob and Trouble!");
		fontMenu.print(buffer, GAME_WIDTH / 3.35, GAME_HEIGHT / 2.5);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Click any button on the keyboard to begin the game!");
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);

		startPlayer.draw();
	}

	if (menuOn == false)
	{	
		space.draw();

		starfield.draw();

		playerMain.draw();

		if (missleShot.missleActive == true)
		{
			missleShot.draw();
		}

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

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "Click 1, 2, 3 or 4 to use Special Abilities!");
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 1.05);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", input->getMouseX());
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 3);

		_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", input->getMouseY());
		dxFont.print(buffer, GAME_WIDTH / 100, GAME_HEIGHT / 4);

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Ability One: Sine Wave Dash
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

		//Ability Two: Bullet Bounce
		for each(Bullet* bullet in bulletList)
		{
			if (bullet->bounceOnCooldown == true)
			{
				//_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)bullet->bounceCooldownTimer);
				//dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);

				_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)bullet->bounceInUseTimer);
				dxFont.print(buffer, playerMain.getCenterX() - 5, playerMain.getCenterY() + 20);
			}

			else
			{
				_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
				dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
			}
		}
		if (bulletList.size() <= 0)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
		}

		//Ability Three: Falling Missle Shot
		if (missleShot.missleOnCooldown == true)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)missleShot.missleCooldownTimer);
			dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
		}

		else
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
		}

		//Ability Four: Reflective Shield
	
		if (playerMain.shieldOnCooldown == true)
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "%d", (int)playerMain.shieldCooldownTimer);
			dxFont.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
		}

		else
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "READY");
			dxFontGreen.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//change ability/specials selection
		if (input->isKeyDown(ONE_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (3 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(TWO_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (2 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(THREE_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (1 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		if (input->isKeyDown(FOUR_KEY))
		{
			_snprintf_s(buffer, spacewarNS::BUF_SIZE, "^");
			fontBig.print(buffer, GAME_WIDTH / 15 * (numberOfSpecials - (0 + 0.8)), GAME_HEIGHT / 10);
			audio->playCue(SELECTION1);
		}

		for each(Bullet*  bullet in bulletList)
		{
			bullet->draw();
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
	heartTexture.onLostDevice();
	specialsTexture.onLostDevice();
	selectionTexture.onLostDevice();
	playerTexture.onLostDevice();
	spaceTexture.onLostDevice();
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
	heartTexture.onResetDevice();
	specialsTexture.onResetDevice();
	selectionTexture.onResetDevice();
	playerTexture.onResetDevice();
	spaceTexture.onResetDevice();
    Game::resetAll();
    return;
}