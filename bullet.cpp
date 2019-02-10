//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity() 
{
	isFired = false; // default to bullet not fired
	spriteData.width = bulletNS::WIDTH;           // size of bullet
	spriteData.height = bulletNS::HEIGHT;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = bulletNS::BULLET_ANIMATION_DELAY;
	startFrame = bulletNS::BULLET_START_FRAME;     // first frame of ship animation
	endFrame = bulletNS::BULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	mass = bulletNS::MASS;
	collisionType = entityNS::BOX;	
}

//=============================================================================
// Initialize
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw bullet
//=============================================================================
void Bullet::draw()
{
	if (isFired == true)
	{
		Image::draw();	
	}	
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime) 
{
	Entity::update(frameTime); 
	
	spriteData.x = spriteData.x + frameTime * velocity.x;
	spriteData.y = spriteData.y + frameTime * velocity.y;

	////////////////////////////////////////////////////////////////////////////////////////////////
	// BounceMan Bounce Shot (Ability 2)
	if (bounceOnCooldown == false)
	{
		if (input->isKeyDown(TWO_KEY))
		{
			bounceManActive = true;
			bounceOnCooldown = true;
		}
	}

	else //bounce shot is on cooldown
	{
		bounceCooldownTimer -= frameTime;
		if (bounceCooldownTimer < 0)
		{
			bounceOnCooldown = false;
			bounceCooldownTimer = 7;
		}
	}

	if (bounceManActive == true)
	{
		bounceInUseTimer -= frameTime;

		if (bounceInUseTimer > 0)
		{
			// Bounce off walls
			if (spriteData.x > GAME_WIDTH - bulletNS::WIDTH)    // if hit right screen edge
			{
				spriteData.x = GAME_WIDTH - bulletNS::WIDTH;    // position at right screen edge
				velocity.x = -velocity.x;                   // reverse X direction				
			}

			else if (spriteData.x < 0)                    // else if hit left screen edge
			{
				spriteData.x = 0;                           // position at left screen edge
				velocity.x = -velocity.x;                   // reverse X direction
			}

			if (spriteData.y > GAME_HEIGHT - bulletNS::HEIGHT)  // if hit bottom screen edge
			{
				spriteData.y = GAME_HEIGHT - bulletNS::HEIGHT;  // position at bottom screen edge
				velocity.y = -velocity.y;                   // reverse Y direction
			}

			else if (spriteData.y < 0)                    // else if hit top screen edge
			{
				spriteData.y = 0;                           // position at top screen edge
				velocity.y = -velocity.y;                   // reverse Y direction
			}
		}

		else //i.e less than zero
		{
			bounceInUseTimer = 4;
			bounceManActive = false;
		}
	}	
	//////////////////////////////////////////////////////////////////////////////////////////
}

void Bullet::shoot(Entity *whereFrom, float frameTime)
{	
	isFired = true;
	spriteData.x = whereFrom->getCenterX() - spriteData.width / 2;
	spriteData.y = whereFrom->getCenterY() - spriteData.height / 2;
	VECTOR2 travel(input->getMouseX() - spriteData.x, input->getMouseY() - spriteData.y);
	Graphics::Vector2Normalize(&travel);
	velocity = travel * bulletNS::SPEED;
}





