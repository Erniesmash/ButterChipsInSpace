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
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Player::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

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
			dashCooldownTimer = 5;
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
			dashInUseTimer = 0.5;
			dashActive = false;
		}
	}

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

	else if (spriteData.y > GAME_HEIGHT - playerNS::HEIGHT * spriteData.scale)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - playerNS::HEIGHT * spriteData.scale;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	if (dashActive == false)
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