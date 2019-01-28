#include "dfr.h"
#include "spacewar.h"

Spacewar *sw;
//=============================================================================
// default constructor
//=============================================================================
Dfr::Dfr() : Entity()
{
	spriteData.width = dfrNS::WIDTH;           // size of Ship1
	spriteData.height = dfrNS::HEIGHT;
	spriteData.x = dfrNS::X;                   // location on screen
	spriteData.y = dfrNS::Y;
	spriteData.rect.bottom = dfrNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfrNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = dfrNS::DFR_ANIMATION_DELAY;
	startFrame = dfrNS::DFR_START_FRAME;     // first frame of Dfr animation
	endFrame = dfrNS::DFR_END_FRAME;     // last frame of Dfr animation
	currentFrame = startFrame;
	radius = dfrNS::WIDTH / 2.0;
	mass = dfrNS::MASS;
	shotTimer = dfrNS::DFR_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	health = 200;
	checkCollided = false;
}

//=============================================================================
// Initialize the Dfr.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfr::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	dfrbTexture.initialize(graphics, DFRBULLET_IMAGE);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the Dfr
//=============================================================================
void Dfr::draw()
{
	Image::draw();
	for each (DfrBullet* b in dfrbList) 
	{
		b->draw();
	}
	// draw Dfr
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Dfr::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * dfrNS::ROTATION_RATE;  // rotate the Dfr
	spriteData.x += frameTime * velocity.x;         // move Dfr along X 
	spriteData.y += frameTime * velocity.y;         // move Dfr along Y

	shoot();
	for each (DfrBullet* b in dfrbList)
	{
		b->update(frameTime);
	}
													// Bounce off walls
	if (spriteData.x > GAME_WIDTH - dfrNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - dfrNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - dfrNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - dfrNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
}

void Dfr::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfrNS::SPEED;
}

void Dfr::shoot()
{
	DfrBullet* b = new DfrBullet;
	b->initialize(sw, dfrbulletNS::WIDTH, dfrbulletNS::HEIGHT, dfrbulletNS::TEXTURE_COLS, &dfrbTexture);
	dfrbList.push_back(b);
}