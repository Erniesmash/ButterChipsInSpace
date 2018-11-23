#include "eship.h"

//=============================================================================
// default constructor
//=============================================================================
EShip::EShip() : Entity()
{
	spriteData.width = eShipNS::WIDTH;           // size of Ship1
	spriteData.height = eShipNS::HEIGHT;
	spriteData.x = eShipNS::X;                   // location on screen
	spriteData.y = eShipNS::Y;
	spriteData.rect.bottom = eShipNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = eShipNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = eShipNS::SHIP_ANIMATION_DELAY;
	startFrame = eShipNS::SHIP1_START_FRAME;     // first frame of EShip animation
	endFrame = eShipNS::SHIP1_END_FRAME;     // last frame of EShip animation
	currentFrame = startFrame;
	radius = eShipNS::WIDTH / 2.0;
	shieldOn = false;
	mass = eShipNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the EShip.
// Post: returns true if successful, false if failed
//=============================================================================
bool EShip::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	shield.setFrames(eShipNS::SHIELD_START_FRAME, eShipNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(eShipNS::SHIELD_START_FRAME);
	shield.setFrameDelay(eShipNS::SHIELD_ANIMATION_DELAY);
	shield.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the EShip
//=============================================================================
void EShip::draw()
{
	Image::draw();              // draw EShip
	if (shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void EShip::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.angle += frameTime * eShipNS::ROTATION_RATE;  // rotate the EShip
	spriteData.x += frameTime * velocity.x;         // move EShip along X 
	spriteData.y += frameTime * velocity.y;         // move EShip along Y

													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - eShipNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - eShipNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - eShipNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - eShipNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	if (shieldOn)
	{
		shield.update(frameTime);
		if (shield.getAnimationComplete())
		{
			shieldOn = false;
			shield.setAnimationComplete(false);
		}
	}
}

//=============================================================================
// damage
//=============================================================================
void EShip::damage(WEAPON weapon)
{
	shieldOn = true;
}