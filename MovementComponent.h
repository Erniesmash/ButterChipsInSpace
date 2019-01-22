#ifndef _MOVEC_H                 // Prevent multiple definitions if this 
#define _MOVEC_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class MovementComponent
{
private:
	int velocity_x;
	int velocity_y;

public:
	void update(float frameTime);
};
#endif