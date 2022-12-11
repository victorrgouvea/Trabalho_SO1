
#include <stdexcept>
#include <iostream>
#include "Player.h"
#include "Laser.h"
#include "GameInput.h"
#include "MainThread.h"

__BEGIN_API


Player::Player()
{
  laserTimer = std::make_shared<Timer> (60);
  laserDelay = 6;
  missileTimer = std::make_shared<Timer> (60);
  missileDelay = 25;
  laserTimer->create();
  missileTimer->create();
  laserTimer->startTimer();
  missileTimer->startTimer();
  speed = Vector(0, 0);
  loadSprites();
}

Player::~Player()
{
	playerSprite.reset();
}

void Player::hit() {
    remainingLifes -= 1;
}

bool Player::alive() {
    return remainingLifes > 0;
}

void Player::fire(std::string fire_type) {
    if (fire_type == "laser") {
        if (laserTimer->getCount() > laserDelay) {
            Laser *laser = new Laser(centre, color, Vector(500, 0));
            MainThread::engine->pushEnemiesProj(laser);
            MainThread::gameWindow->addProjectile(laser);
            laserTimer->srsTimer();
	    }
    /*
    } else if (fire_type == "missile") {
        if (missileTimer->getCount() > missileDelay) {
            Missile *missile = new Missile(centre, color, 400, true);
            // Trata de desenhar o sprite
            MainThread::_window->addDrawableItem(missile);
            // Trata de calcular a colisão do tiro
            MainThread::_collision->addPlayerShot(missile);
            missileTimer->srsTimer();
	    }
    }
    */
  }
}

void Player::run()
{
	while (MainThread::gameWindow->getGameRunning())
	{

		if (MainThread::gameWindow == nullptr || MainThread::engine == nullptr)
			Thread::yield();
		handleInput();
		Thread::yield();
	}
    std::cout << "chegou aqui\n";
}

void Player::draw()
{
	playerSprite->draw_region(row, col, 47.0, 40.0, centre, 0);
}

void Player::update(double diffTime)
{
	centre =  centre + this->speed * diffTime;
	selectShipAnimation(); // must happen before we reset our speed
	speed = Vector(0, 0);	 // reset our speed
	checkBoundary();
}

bool Player::isOutside()
{
	if ((centre.x > MainThread::gameWindow->getWidth()) ||
			(centre.x < 0) ||
			(centre.y > MainThread::gameWindow->getHeight()) ||
			(centre.y < 0))
			return true;
  return false;
	};

void Player::handleInput() {

  act::action inputEvent = MainThread::gamekeyb->getInputEvent();
  if (inputEvent == act::action::MOVE_UP) {
    speed.y -= 250;
  }
  if (inputEvent == act::action::MOVE_RIGHT) {
    speed.x += 250;
  }
  if (inputEvent == act::action::MOVE_DOWN) {
    speed.y += 250;
  }
  if (inputEvent == act::action::MOVE_LEFT) {
    speed.x -= 250;
  }
  if (inputEvent == act::action::FIRE_SECONDARY) {
    fire("missile");
  }
  if (inputEvent == act::action::FIRE_PRIMARY) {
    fire("laser");
  }
}

void Player::selectShipAnimation() {
   if (speed.x > 0) {
      col = 1;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   } else {
      col = 0;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   }
}

void Player::checkBoundary() {   
   // check x bound and adjust if out
   if (centre.x > 800 - 16)
      centre.x = 800 - 16;
   else if (centre.x < 16)
      centre.x = 16;   
   // check y bound and adjust if out
   if (centre.y > 600 - 16)
      centre.y = 600 - 16;
   else if (centre.y < 16)
      centre.y = 16;
}


void Player::loadSprites()
{
	spritesLoaded = true;

	// Create Ship
    centre = Point(215, 245);
    color= al_map_rgb(0, 200, 0);

	// Go to resources directory
	ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
	al_append_path_component(path, "resources");
	al_change_directory(al_path_cstr(path, '/'));

	// sprites
	playerSprite = std::make_shared<Sprite>("Sprite2.png");

	// delete path
	al_destroy_path(path);
}

__END_API