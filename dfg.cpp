#include "dfg.h"
#include "spacewar.h"

//=============================================================================
// default constructor
//=============================================================================
Dfg::Dfg() : Entity()
{
	spriteData.width = dfgNS::WIDTH;           // size of Ship1
	spriteData.height = dfgNS::HEIGHT;
	spriteData.x = dfgNS::X;                   // location on screen
	spriteData.y = dfgNS::Y;
	spriteData.rect.bottom = dfgNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = dfgNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = dfgNS::DFG_ANIMATION_DELAY;
	startFrame = dfgNS::DFG_START_FRAME;     // first frame of Dfg animation
	endFrame = dfgNS::DFG_END_FRAME;     // last frame of Dfg animation
	currentFrame = startFrame;
	radius = dfgNS::WIDTH / 2.0;
	mass = dfgNS::MASS;
	health = dfgNS::DFG_HEALTH;
	shotTimer = dfgNS::DFG_SHOT_TIMER;
	collisionType = entityNS::CIRCLE;
	shot = false;
	dead = false;
	imgChanged = false;
}

//=============================================================================
// Initialize the Dfg.
// Post: returns true if successful, false if failed
//=============================================================================
bool Dfg::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	sw = gamePtr;
	//dfgbTexture.initialize(graphics, DFGBULLET_IMAGE);
	//hbTexture.initialize(graphics, HEALTHBAR_IMAGE);
	hb.initialize(sw, hbNS::WIDTH, hbNS::HEIGHT, hbNS::TEXTURE_COLS, &hbTexture);
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

//=============================================================================
// draw the Dfg
//=============================================================================
void Dfg::draw()
{
	Image::draw();
	for each (DfgBullet* b in dfgbList)
	{
		b->draw();
	}
	hb.draw();
	// draw Dfg
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Dfg::update(float frameTime)
{
	shotTimer -= frameTime;
	Entity::update(frameTime);
	spriteData.angle += frameTime * dfgNS::ROTATION_RATE;  // rotate the Dfg
	spriteData.x += frameTime * velocity.x;         // move Dfg along X 
	spriteData.y += frameTime * velocity.y;         // move Dfg along Y

	//initialize
	dfgbTexture.initialize(graphics, DFGBULLET_IMAGE);
	hbTexture.initialize(graphics, HEALTHBAR_IMAGE);

	hb.setY(spriteData.y - hbNS::HEIGHT);
	hb.setX(getCenterX() - hbNS::WIDTH / 2);
	hb.setWidth((health / dfgNS::DFG_HEALTH) * hbNS::WIDTH);

	hb.update(frameTime);
	/*if (currentFrame == 11)
	{
		shot = false;
	}
	if (currentFrame == 10 && shot == false)
	{
		shoot();
		shot = true;
	}*/


	for each (DfgBullet* b in dfgbList)
	{
		b->update(frameTime);
	}
	// Bounce off walls
	if (spriteData.x > GAME_WIDTH - dfgNS::WIDTH)    // if hit right screen edge
	{
		spriteData.x = GAME_WIDTH - dfgNS::WIDTH;    // position at right screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	else if (spriteData.x < 0)                    // else if hit left screen edge
	{
		spriteData.x = 0;                           // position at left screen edge
		velocity.x = -velocity.x;                   // reverse X direction
	}
	if (spriteData.y > GAME_HEIGHT - dfgNS::HEIGHT)  // if hit bottom screen edge
	{
		spriteData.y = GAME_HEIGHT - dfgNS::HEIGHT;  // position at bottom screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}
	else if (spriteData.y < 0)                    // else if hit top screen edge
	{
		spriteData.y = 0;                           // position at top screen edge
		velocity.y = -velocity.y;                   // reverse Y direction
	}

	if (input->isKeyDown(VK_SPACE))
	{
		if (health >= 0)
		{
			health = health - 1;
		}
	}

	if (health <= 0)
	{
		dead = true;
	}
}

void Dfg::chase(Entity *target)
{
	VECTOR2 travel(target->getCenterX() - getCenterX(), target->getCenterY() - getCenterY());
	Graphics::Vector2Normalize(&travel);
	velocity = travel * dfgNS::SPEED;
}

void Dfg::shoot()
{

	for (int i = -3; i < 3; i++)
	{
		DfgBullet* d = new DfgBullet;
		d->initialize(sw, dfgbulletNS::WIDTH, dfgbulletNS::HEIGHT, dfgbulletNS::TEXTURE_COLS, &dfgbTexture);
		d->appImpulse(getX(), getY(), 0, getY() + (i));
		dfgbList.push_back(d);
	}
}

float Dfg::dir(float fromx, float fromy, float tox, float toy)
{
	VECTOR2 from(fromx, fromy);
	VECTOR2 to(tox, toy);
	float angle = acos((Graphics::Vector2Dot(&from, &to) / Graphics::Vector2Length(&from)*Graphics::Vector2Length(&to)));
	return 0;
}

void Dfg::wave()
{
	DfgBullet* a = new DfgBullet;
	a->initialize(sw, dfgbulletNS::WIDTH, dfgbulletNS::HEIGHT, dfgbulletNS::TEXTURE_COLS, &dfgbTexture);
	a->invert = true;
	a->wavy(this);
	dfgbList.push_back(a);

	DfgBullet* b = new DfgBullet;
	b->initialize(sw, dfgbulletNS::WIDTH, dfgbulletNS::HEIGHT, dfgbulletNS::TEXTURE_COLS, &dfgbTexture);
	b->wavy(this);
	dfgbList.push_back(b);
}

void Dfg::healthBar()
{
}