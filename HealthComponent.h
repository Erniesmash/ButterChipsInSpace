#ifndef _HEALTHC_H                 // Prevent multiple definitions if this 
#define _HEALTHC_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class HealthComponent
{
private:
	int max_health;
	int curr_health;
	bool isAlive;

public:
	void update(float frameTime);
};
#endif
