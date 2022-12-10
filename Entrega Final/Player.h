#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "Threads/thread.h"
#include "Threads/traits.h"
#include "GameInput.h"
#include "Sprite.h"
#include "Vector.h"
#include "Action.h"
#include "Point.h"
#include "GameWindow.h"
#include "Laser.h"
#include "Timer.h"
#include "Engine.h"
#include <string.h>

__BEGIN_API

class Collision;

class Player {

public:
	Player();
	~Player();

	
	void run();
	void draw();
	void hit();
	bool alive();
	bool isOutside();
	void update(double diffTime);
    Point getCentre() { return centre; }
    void handleInput();
	void fire(string fire_type);
    void checkBoundary();
	void updateShipAnimation();



private:

	ALLEGRO_COLOR color;
	std::shared_ptr<Timer> laserTimer;
	std::shared_ptr<Timer> missileTimer;
    int laserDelay;
	int missileDelay;
    int remainingLifes = 3;

	// Draw information
	std::shared_ptr<Sprite> playerSprite;
	Point centre;       /**< ship position */
	Vector speed;		/**< movement speed in any direction */
	int row;			/**<row of animation to be played */
	int col;			/**< column of animation to be played */
	void loadSprites();
	bool spritesLoaded = false;
};

__END_API

#endif