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
	bool alive();
	void update(double diffTime);
    Point getCentre() { return centre; }
    void handleInput();
	void fire(std::string fire_type);
    void checkBoundary();
	void selectShipAnimation();
	bool isOutside();
	Point getPosition() { return centre; }
	int getSize() { return playerSize; }  // Retorna o tamanho da nave hardcoded

private:

	ALLEGRO_COLOR color;
	std::shared_ptr<Timer> laserTimer;
	std::shared_ptr<Timer> missileTimer;
    int laserDelay;
	int missileDelay;
    int remainingLifes = 3;
	int playerSize = 16;

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