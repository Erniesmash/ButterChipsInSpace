#include "rocket.h"
#include "speedboost.h"

//=============================================================================
// default constructor
//=============================================================================
Rocket::Rocket() : Entity()
{
	spriteData.width = rocketNS::WIDTH;           // size of rocket
	spriteData.height = rocketNS::HEIGHT;
	spriteData.x = rocketNS::X;                   // location on screen
	spriteData.y = rocketNS::Y;
	spriteData.rect.bottom = rocketNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = rocketNS::WIDTH;
	velocity.x = 1.0;                             // velocity X
	velocity.y = 1.0;                             // velocity Y
	frameDelay = rocketNS::ROCKET_ANIMATION_DELAY;
	startFrame = rocketNS::ROCKET_START_FRAME;     // first frame of ship animation
	endFrame = rocketNS::ROCKET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = rocketNS::WIDTH / 2.0;
	mass = rocketNS::MASS;
	collisionType = entityNS::CIRCLE;
	bulletSpeedActivated = false;
	sbActive = false;
	sbTimer = rocketNS::SB_TIMER;
	spd = rocketNS::SPEED;
	health = 600;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Rocket::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Rocket::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Rocket::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * rocketNS::ROTATION_RATE;  // rotate the ship
	//spriteData.x += frameTime * velocity.x;         // move ship along X 
	//spriteData.y += frameTime * velocity.y;         // move ship along Y
	if (sbActive)
	{
		sbTimer -= frameTime;
		spd = speedboostNS::BOOST;
	}
	else if (sbActive == false)
	{
		sbTimer = 15.0f;
		spd = rocketNS::SPEED;
	}
	
	if (sbTimer <= 0)
	{
		sbActive = false;
	}

	if (bulletSpeedActivated == true)
	{
		bulletSpeedTimer -= frameTime;
	}

	if (bulletSpeedActivated == false)
	{
		bulletSpeedTimer = 10.0f; //reset
	}

	if (bulletSpeedTimer <= 0)
	{
		bulletSpeedActivated = false;
	}

	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - rocketNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - rocketNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - rocketNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - rocketNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	if (input->isKeyDown(ROCKET_D_KEY))            // if move right
	{
		spriteData.x = spriteData.x + frameTime * spd;
	}
	
	if (input->isKeyDown(ROCKET_A_KEY))             // if move left
	{
		spriteData.x = spriteData.x - frameTime * spd;
	}

	if (input->isKeyDown(ROCKET_W_KEY))               // if move up
	{
		spriteData.y = spriteData.y - frameTime * spd;
	}

	if (input->isKeyDown(ROCKET_S_KEY))             // if move down
	{
		spriteData.y = spriteData.y + frameTime * spd;
	}

	if (input->isKeyDown(ROCKET_E_KEY))
	{
		spriteData.angle += frameTime * rocketNS::ROTATION_RATE;
	}

	if (input->isKeyDown(ROCKET_Q_KEY))
	{
		spriteData.angle -= frameTime * rocketNS::ROTATION_RATE;
	}
}
