#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity() 
{
	spriteData.width = bulletNS::WIDTH;           // size of bullet
	spriteData.height = bulletNS::HEIGHT;
	spriteData.x = GAME_WIDTH / 4;                   // location on screen
	spriteData.y = GAME_HEIGHT /2;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	velocity.x = 10;
	velocity.y = 10;
	frameDelay = bulletNS::BULLET_ANIMATION_DELAY;
	startFrame = bulletNS::BULLET_START_FRAME;     // first frame of ship animation
	endFrame = bulletNS::BULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	mass = bulletNS::MASS;
	collisionType = entityNS::CIRCLE;	
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
	Image::draw();              // draw bullet
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime) 
{
	//set sprite data positions to unit vector x frametime
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;     // move along X 
	spriteData.y += frameTime * velocity.y;     // move along Y
}


//=============================================================================
// damage
//=============================================================================
void Bullet::damage(WEAPON weapon){}

void Bullet::fire(Entity *ship)
{	
	velocity.x = bulletNS::SPEED;
	velocity.y = bulletNS::SPEED;
	spriteData.x = ship->getCenterX() - spriteData.width / 2;
	spriteData.y = ship->getCenterY() - spriteData.height / 2;
}
