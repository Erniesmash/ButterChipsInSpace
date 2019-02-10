//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "player.h"

//=============================================================================
// default constructor
//=============================================================================

Player::Player() : Entity()
{
	spriteData.width = playerNS::WIDTH;           // size of rocket
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;                   // location on screen
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerNS::WIDTH;
	velocity.x = 1.0;                             // velocity X
	velocity.y = 1.0;                             // velocity Y
	frameDelay = playerNS::PLAYER_ANIMATION_DELAY;
	startFrame = playerNS::PLAYER_START_FRAME;     // first frame of ship animation
	endFrame = playerNS::PLAYER_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = playerNS::WIDTH / 2.0;
	mass = playerNS::MASS;
	collisionType = entityNS::BOX;
	shieldOn = false;
	dialogueChoice = 1;
	dialogueEnd = false;
	health = 6;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	// shield texture
	if (!shieldTexture.initialize(gamePtr->getGraphics(), SHIELD_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield texture"));

	// shield
	shield.initialize(gamePtr->getGraphics(), playerNS::SHIELD_WIDTH, playerNS::SHIELD_HEIGHT, playerNS::SHIELD_COLS, &shieldTexture);
	shield.setFrames(playerNS::SHIELD_START_FRAME, playerNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(playerNS::SHIELD_START_FRAME);
	shield.setFrameDelay(playerNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
	if (health > 0)
	{
		Image::draw();		
	}    

	else
	{
		active = false;
	}

	if (shieldOn == true)
	{
		shield.draw(graphicsNS::ALPHA50 & colorFilter);
		shield.setX(spriteData.x - spriteData.width / 2 * spriteData.scale);
		shield.setY(spriteData.y - spriteData.height / 2 * spriteData.scale);
		shield.setScale(0.5);
	}		
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

	if (shieldOn)
	{
		shield.update(frameTime);
	}

	if (dialogueChoice == 1)
	{
		playerDialogue = "I have to defeat him before...";
	}

	if (dialogueChoice == 2)
	{
		playerDialogue = "...it is too late!";
	}

	if (dialogueChoice == 3)
	{
		playerDialogue = "The world is at stake!";
	}

	if (dialogueChoice == 4)
	{
		playerDialogue = "I must protect...";
	}

	if (dialogueChoice == 5)
	{
		playerDialogue = "...the things I love!";
	}

	if (dialogueChoice == 6)
	{
		dialogueEnd = true;
	}

	/*
	enum State{STATE_IDLE, STATE_ATTACK};
	switch(state_)
	{
		case STATE_IDLE:

		case STATE_ATTACK:

	}
	*/	

	// Rotate Player Sprite based on Cursor Position
	/*
	float theta;
	
	VECTOR2 travel(input->getMouseX(), input->getMouseY());
	VECTOR2 origin(spriteData.x, spriteData.y);
	theta = acos(graphics->Vector2Dot(&travel, &origin) / graphics->Vector2Length(&travel) + graphics->Vector2Length(&origin));
	spriteData.angle += (theta/180 * PI) * frameTime;
	*/
	/*
	float delta_x;
	float delta_y;
	delta_y = spriteData.y - input->getMouseY();
	delta_x = spriteData.x - input->getMouseX();
	theta = atan2(delta_y, delta_x);
	*/

	//spriteData.angle += frameTime * theta;
	
	/*
	if (input->isKeyDown(ROCKET_E_KEY))      
	{
		spriteData.angle += frameTime * playerNS::ROTATION_RATE;
	}
	*/
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// Sine Wave Dodge Roll (Ability 1)
	if (dashOnCooldown == false)
	{
		if (input->isKeyDown(ONE_KEY))
		{
			dashActive = true;
			dashOnCooldown = true;
		}
	}

	else //dash is on cooldown
	{
		dashCooldownTimer -= frameTime;
		if (dashCooldownTimer < 0)
		{
			dashOnCooldown = false;
			dashCooldownTimer = 3; //Change this value to adjust cooldown
		}
	}
	
	if (dashActive == true)
	{
		dashInUseTimer -= frameTime;

		if (dashInUseTimer > 0)
		{
			spriteData.x = spriteData.x + frameTime * playerNS::SPEED;
			spriteData.y = spriteData.y + 6 * sin(0.09 * spriteData.x);
		}	

		else //i.e less than zero
		{
			dashInUseTimer = 0.5; //change this value to adjust how long dash is active, dont forget inital timer too
			dashActive = false;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////
	// Reflective Shield (Ability 4)

	if (shieldOnCooldown == false)
	{
		if (input->isKeyDown(FOUR_KEY))
		{
			shieldOn = true;
			shieldOnCooldown = true;
		}
	}

	else //dash is on cooldown
	{
		shieldCooldownTimer -= frameTime;
		if (shieldCooldownTimer < 0)
		{
			shieldOnCooldown = false;
			shieldCooldownTimer = 12; //Change this value to adjust cooldown
		}
	}

	if (shieldOn == true)
	{
		shieldInUseTimer -= frameTime;

		if (shieldInUseTimer > 0)
		{
			shieldOn = true;
		}

		else //i.e less than zero
		{
			shieldInUseTimer = 5; //change this value to adjust how long shield is active
			shieldOn = false;
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - playerNS::WIDTH * spriteData.scale)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - playerNS::WIDTH * spriteData.scale;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}

	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}

	if (spriteData.y > GAME_HEIGHT - playerNS::HEIGHT * spriteData.scale)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - playerNS::HEIGHT * spriteData.scale;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	if (dashActive == false) // Prevent player from affecting sine wave
	{
		if (input->isKeyDown(ROCKET_D_KEY))            // if move right
		{
			spriteData.x = spriteData.x + frameTime * playerNS::SPEED;
		}

		if (input->isKeyDown(ROCKET_A_KEY))             // if move left
		{
			spriteData.x = spriteData.x - frameTime * playerNS::SPEED;
		}

		if (input->isKeyDown(ROCKET_W_KEY))               // if move up
		{
			spriteData.y = spriteData.y - frameTime * playerNS::SPEED;
		}

		if (input->isKeyDown(ROCKET_S_KEY))             // if move down
		{
			spriteData.y = spriteData.y + frameTime * playerNS::SPEED;
		}
	}
}