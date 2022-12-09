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
#include "Missile.h"
#include "Timer.h"
#include "Hittable.h"
#include "Collision.h"
#include <string>

__BEGIN_API

class Collision;

class Player : public Hittable
{

public:
	Player();
	~Player();

	void setWindowReference(Window *window) { this->_window = window; }
	void setCollisionReference(Collision *collision) { this->_collision = collision; }
	void run();
	void draw();
	void hit(int damage);
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
	// Objects variables
	Window *_window;
	Collision *_collision;

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