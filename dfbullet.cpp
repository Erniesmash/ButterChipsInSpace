#include "dfr.h"
#include "dfbullet.h"

//=============================================================================
// default constructor
//=============================================================================
DfBullet::DfBullet() : Entity()
{
	spriteData.width = dfbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfbulletNS::HEIGHT;
	spriteData.x = dfbulletNS::X;                   // location on screen
	spriteData.y = dfbulletNS::Y;
	spriteData.rect.bottom = dfbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfbulletNS::DFBULLET_ANIMATION_DELAY;
	startFrame = dfbulletNS::DFBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfbulletNS::DFBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfbulletNS::WIDTH / 2.0;
	mass = dfbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
}

//=============================================================================
// Initialize the DfBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfbulletNS::ROTATION_RATE;  // rotate the ship
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y


	// destroy at walls
	if (spriteData.x > GAME_WIDTH - dfbulletNS::WIDTH)    // if hit right screen edge
	{
		collided = true;
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		collided = true;
	}
	if (spriteData.y > GAME_HEIGHT - dfbulletNS::HEIGHT)  // if hit bottom screen edge
	{
		collided = true;
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		collided = true;
	}
}

void DfBullet::getDir(Entity *to, Entity *from)
{
	spriteData.x = from->getCenterX() - spriteData.width / 2;
	spriteData.y = from->getCenterY() - spriteData.height / 2;
	VECTOR2 travel(to->getCenterX() - getCenterX(), to->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfbulletNS::SPEED;
}