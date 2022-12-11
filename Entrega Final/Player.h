#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "thread.h"
#include "traits.h"
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
#include "Missile.h"

__BEGIN_API

class Collision;

class Player: public Drawable {

public:
	Player();
	~Player();
	
	void run();
	void draw();
	void hit();
	void update(double diffTime);
    Point getCentre() { return centre; }
    void handleInput();
	void fire(std::string fire_type);
    void checkBoundary();
	void selectShipAnimation();
	bool in_bound();
	int getLives() { return remainingLifes; };
	Point getPosition() { return centre; }
	int getSize() { return size; }  // Retorna o tamanho da nave hardcoded
	bool getAlive() { return alive; }
	ALLEGRO_COLOR color;

private:

	std::shared_ptr<Timer> laserTimer;
	std::shared_ptr<Timer> missileTimer;
    int laserDelay;
	bool alive;
	int missileDelay;
    int remainingLifes = 3;
	int size;
	std::string classType() { return "player"; }
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