//  Module:             Gameplay Programming
//  Assignment2:        Blob and Trouble
//  Student Name:       Tan Cheng Hian
//  Student Number:     S10179071A
//  Student Name:       Ernest Cheo
//  Student Number:     S10177445D

#include "dfg.h"
#include "dfgbullet.h"

//=============================================================================
// default constructor
//=============================================================================
DfgBullet::DfgBullet() : Entity()
{
	spriteData.width = dfgbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfgbulletNS::HEIGHT;
	spriteData.x = dfgbulletNS::X;                   // location on screen
	spriteData.y = dfgbulletNS::Y;
	spriteData.rect.bottom = dfgbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfgbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfgbulletNS::DFGBULLET_ANIMATION_DELAY;
	startFrame = dfgbulletNS::DFGBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfgbulletNS::DFGBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfgbulletNS::WIDTH / 2.0;
	mass = dfgbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
	bounce = false;
}

//=============================================================================
// Initialize the DfgBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfgBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfgBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfgBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfgbulletNS::ROTATION_RATE;  // rotate the ship
	spriteData.x += frameTime * velocity.x; //* velocity.x;         // move ship along X
	spriteData.y += frameTime * velocity.y;         // move ship along Y*/

	if (bounce == true)
	{
		if (spriteData.x > GAME_WIDTH - dfgbulletNS::WIDTH)    // if hit right screen edge
		{
			spriteData.x = GAME_WIDTH - dfgbulletNS::WIDTH;    // position at right screen edge
			velocity.x = -velocity.x;                   // reverse X direction
			bounce = false;
		}

		if (spriteData.y > GAME_HEIGHT - dfgbulletNS::HEIGHT)  // if hit bottom screen edge
		{
			spriteData.y = GAME_HEIGHT - dfgbulletNS::HEIGHT;  // position at bottom screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
			bounce = false;
		}
		else if (spriteData.y < 0)                    // else if hit top screen edge
		{
			spriteData.y = 0;                           // position at top screen edge
			velocity.y = -velocity.y;                   // reverse Y direction
			bounce = false;
		}
	}

	if (bounce == false)
	{
		// destroy at walls
		if (spriteData.x > GAME_WIDTH + dfgbulletNS::WIDTH * 2)    // if hit right screen edge
		{
			collided = true;
		}
		else if (spriteData.x < -dfgbulletNS::WIDTH * 2)                    // else if hit left screen edge
		{
			collided = true;
		}
		if (spriteData.y > GAME_HEIGHT + dfgbulletNS::HEIGHT * 2)  // if hit bottom screen edge
		{
			collided = true;
		}
		else if (spriteData.y < -dfgbulletNS::HEIGHT * 2)                    // else if hit top screen edge
		{
			collided = true;
		}
	}
}

void DfgBullet::appImpulse(float xpos, float ypos, double angle, float speed)
{
	spriteData.x = xpos - spriteData.width / 2;
	spriteData.y = ypos - spriteData.height / 2;

	//D3DXMATRIX matrix;
	//D3DXMatrixTranslation

	VECTOR2 ref(GAME_WIDTH - getCenterX(), 0);
	//VECTOR2 travel = matrix * ref;
	VECTOR2 travel(Graphics::Vector2Length(&ref)*cos((angle / 360)*(2 * PI)), Graphics::Vector2Length(&ref)*sin((angle / 360)*(2 * PI)));
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}

void DfgBullet::getDir(float x, float y, float fromx, float fromy, float speed)
{
	spriteData.x = fromx - spriteData.width / 2;
	spriteData.y = fromy - spriteData.height / 2;
	VECTOR2 travel(x - getCenterX(), y - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}