#include "powerup.h"

//=============================================================================
// default constructor
//=============================================================================
Powerup::Powerup() : Entity()
{
	spriteData.width = powerupNS::WIDTH;           // size of rocket
	spriteData.height = powerupNS::HEIGHT;
	spriteData.x = powerupNS::X;                   // location on screen
	spriteData.y = powerupNS::Y;
	spriteData.rect.bottom = powerupNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = powerupNS::WIDTH;
	spriteData.scale = 0.2;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = powerupNS::POWERUP_ANIMATION_DELAY;
	startFrame = powerupNS::POWERUP_START_FRAME;     // first frame of ship animation
	endFrame = powerupNS::POWERUP_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = powerupNS::WIDTH / 2.0;
	mass = powerupNS::MASS;
	collisionType = entityNS::CIRCLE;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Powerup::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Powerup::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Powerup::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - powerupNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - powerupNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - powerupNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - powerupNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
}
