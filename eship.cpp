//  Module:             Gameplay Programming
//  Assignment1:        Butter Chips in Space
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "eship.h"
#include "ebullet.h"

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
	frameDelay = eShipNS::ESHIP_ANIMATION_DELAY;
	startFrame = eShipNS::ESHIP1_START_FRAME;     // first frame of EShip animation
	endFrame = eShipNS::ESHIP1_END_FRAME;     // last frame of EShip animation
	currentFrame = startFrame;
	radius = eShipNS::WIDTH / 2.0;
	mass = eShipNS::MASS;
	shotTimer = eShipNS::ESHIP_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	health = 200;
	checkCollided = false;
}

//=============================================================================
// Initialize the EShip.
// Post: returns true if successful, false if failed
//=============================================================================
bool EShip::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the EShip
//=============================================================================
void EShip::draw()
{
	Image::draw();
            // draw EShip
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void EShip::update(float frameTime)
{
	shotTimer -= frameTime;
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
}

void EShip::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * eShipNS::SPEED;
}

/*void EShip::shoot()
{
	if (waitShotTimer <= 0.0f)
	{
		waitShotTimer = bulletNS::WAIT_SHOOT; //Resets the shotTimer using namespace value
		isFired = true;
		velocity.x = cos(whereFrom->getRadians()) * bulletNS::SPEED;
		velocity.y = sin(whereFrom->getRadians()) * bulletNS::SPEED;
		spriteData.x = whereFrom->getCenterX() - spriteData.width / 2;
		spriteData.y = whereFrom->getCenterY() - spriteData.height / 2;
	}
}*/
