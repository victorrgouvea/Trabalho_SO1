
#include <stdexcept>
#include <iostream>
#include "Player.h"
#include "Laser.h"
#include "GameInput.h"
#include "MainThread.h"

__BEGIN_API


Player::Player()
{
  size = 16;
  color = al_map_rgb(150, 0, 0);
  laserTimer = std::make_shared<Timer> (60);
  laserDelay = 6;
  missileTimer = std::make_shared<Timer> (60);
  missileDelay = 25;
  laserTimer->create();
  missileTimer->create();
  laserTimer->startTimer();
  missileTimer->startTimer();
  speed = Vector(0, 0);
  alive = true;
  loadSprites();
}

Player::~Player()
{
	playerSprite.reset();
}

void Player::hit() {
    remainingLifes -= 1;
    if (remainingLifes < 1) {
      alive = false;
    }
}

void Player::fire(std::string fire_type) {
    if (fire_type == "laser") {
        if (laserTimer->getCount() > laserDelay) {
            Laser *laser = new Laser(centre, al_map_rgb(150, 0, 0), Vector(500, 0), true);
            MainThread::gameWindow->addSprite(laser);
            MainThread::engine->addProj(laser);
            laserTimer->srsTimer();
	    }
    
    } else if (fire_type == "missile") {
        if (missileTimer->getCount() > missileDelay) {
            Missile *missile = new Missile(centre, al_map_rgb(150, 0, 0), Vector(500, 0), true);
            MainThread::gameWindow->addSprite(missile);
            MainThread::engine->addProj(missile);
            missileTimer->srsTimer();
	    }
    }
}

void Player::run()
{
	while (MainThread::gameWindow->getGameRunning())
	{
		if (MainThread::engine == nullptr)
			Thread::yield();
		handleInput();
		Thread::yield();
	}
}

void Player::draw()
{
	playerSprite->draw_region(row, col, 47.0, 40.0, centre, 0);
}

void Player::update(double diffTime)
{
	centre =  centre + speed * diffTime;
	selectShipAnimation(); // must happen before we reset our speed
	speed = Vector(0, 0);	 // reset our speed
	checkBoundary();
}

bool Player::in_bound()
{
	if ((centre.x > MainThread::gameWindow->getWidth()) ||
			(centre.x < 0) ||
			(centre.y > MainThread::gameWindow->getHeight()) ||
			(centre.y < 0))
			return true;
  return false;
	};

void Player::handleInput() {
	if (MainThread::gamekeyb->getInputEvent(act::action::MOVE_UP))
		this->speed.y -= 250;
	if (MainThread::gamekeyb->getInputEvent(act::action::MOVE_DOWN))
		this->speed.y += 250;
	if (MainThread::gamekeyb->getInputEvent(act::action::MOVE_LEFT))
		this->speed.x -= 250;
	if (MainThread::gamekeyb->getInputEvent(act::action::MOVE_RIGHT))
		this->speed.x += 250;
	if (MainThread::gamekeyb->getInputEvent(act::action::FIRE_SECONDARY)) {
    fire("missile");
  }
  if (MainThread::gamekeyb->getInputEvent(act::action::FIRE_PRIMARY)) {
    fire("laser");
  }
  if (MainThread::gamekeyb->getInputEvent(act::action::QUIT_GAME)) {
    MainThread::gameWindow->setGameRunning(false);
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
   MainThread::gameWindow->addSprite(this);
	// delete path
	al_destroy_path(path);
}

__END_API