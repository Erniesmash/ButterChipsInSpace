#include "dfr.h"
#include "dfrbullet.h"

//=============================================================================
// default constructor
//=============================================================================
DfrBullet::DfrBullet() : Entity()
{
	spriteData.width = dfrbulletNS::WIDTH;           // size of Ship1
	spriteData.height = dfrbulletNS::HEIGHT;
	spriteData.x = dfrbulletNS::X;                   // location on screen
	spriteData.y = dfrbulletNS::Y;
	spriteData.rect.bottom = dfrbulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfrbulletNS::WIDTH;
	velocity.x = 1;                             // velocity X
	velocity.y = 1;                             // velocity Y
	frameDelay = dfrbulletNS::DFRBULLET_ANIMATION_DELAY;
	startFrame = dfrbulletNS::DFRBULLET_START_FRAME;     // first frame of ship animation
	endFrame = dfrbulletNS::DFRBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = dfrbulletNS::WIDTH / 2.0;
	mass = dfrbulletNS::MASS;
	collisionType = entityNS::CIRCLE;
	collided = false;
}

//=============================================================================
// Initialize the DfrBullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool DfrBullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void DfrBullet::draw()
{
	Image::draw();              // draw ship
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void DfrBullet::update(float frameTime)
{
	Entity::update(frameTime);
	//spriteData.angle += frameTime * dfrbulletNS::ROTATION_RATE;  // rotate the ship

	//for spray and 1 shot
	
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y*/

	// destroy at walls
	if (spriteData.x > GAME_WIDTH - dfrbulletNS::WIDTH)    // if hit right screen edge
	{
		collided = true;
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		collided = true;
	}
	if (spriteData.y > GAME_HEIGHT - dfrbulletNS::HEIGHT)  // if hit bottom screen edge
	{
		collided = true;
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		collided = true;
	}
}

void DfrBullet::getDir(float x, float y, float fromx, float fromy, float speed)
{
	spriteData.x = fromx - spriteData.width / 2;
	spriteData.y = fromy - spriteData.height / 2;
	VECTOR2 travel(x - getCenterX(), y - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}

void DfrBullet::appImpulse(float xpos, float ypos, float angle, float speed)
{
	spriteData.x = xpos - spriteData.width / 2;
	spriteData.y = ypos - spriteData.height / 2;

	//D3DXMATRIX matrix;
	//D3DXMatrixTranslation

	VECTOR2 ref(0 - getCenterX(), 0);
	//VECTOR2 travel = matrix * ref;
	VECTOR2 travel(Graphics::Vector2Length(&ref)*cos((angle / 360)*(2 * PI)), Graphics::Vector2Length(&ref)*sin((angle / 360)*(2 * PI)));
	Graphics::Vector2Normalize(&travel);
	velocity = travel * speed;
}