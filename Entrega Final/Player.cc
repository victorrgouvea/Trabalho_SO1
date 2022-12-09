include <stdexcept>
#include <iostream>

#include "Player.h"
#include "Laser.h"
#include "GameInput.h"
#include "MainThread.h"


__BEGIN_API


Player::Player()
{
	laserTimer = std::make_shared<Timer>(GameConfigs::fps);
    laserDelay = 6;
	missileTimer = std::make_shared<Timer>(GameConfigs::fps);
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
    this->life -= 1;
}

bool Player::alive() {
    return remainingLifes > 0;
}

void Player::fire(string fire_type) {
    if (fire_type == 'laser') {
        if (laserTimer->getCount() > laserDelay) {
            Laser *laser new Laser(centre, color, 500, true);
            // Trata de desenhar o sprite
            MainThread::_collision->addPlayerShot(laser);
            // Trata de calcular a colisão do tiro
            MainThread::_window->addDrawableItem(laser);
            laserTimer->srsTimer();
	    }
    } else if (fire_type == 'missile') {
        if (missileTimer->getCount() > missileDelay) {
            Missile *missile = new Missile(centre, color, 400, true);
            // Trata de desenhar o sprite
            MainThread::_window->addDrawableItem(missile);
            // Trata de calcular a colisão do tiro
            MainThread::_collision->addPlayerShot(missile);
            missileTimer->srsTimer();
	    }
    }
}




bool Player::isOutside() { return (!this->isDead()); }

void Player::run()
{
	while (!GameConfigs::finished)
	{
		// Não executa enquanto as referências não forem corretas
		if (this->_window == nullptr || this->_collision == nullptr)
			Thread::yield();

		this->processAction();
		Thread::yield();
	}
}

void Player::draw()
{
	this->shipSprite->draw_region(this->row, this->col, 47.0, 40.0, this->shipPosition, 0);
}

void Player::update(double diffTime)
{
	centre = this->shipPosition + this->speed * diffTime;
	updateShipAnimation(); // must happen before we reset our speed
	speed = Vector(0, 0);	 // reset our speed
	checkExceedingWindowLimit();
}

void Player::handleInput() {

  act::action inputEvent = MainThread::kBoardObj->getInputEvent();
  if (inputEvent == act::action::MOVE_UP) {
    speed.y -= 250;
  }
  if (inputEvent == act::action::MOVE_RIGHT) {
    speed.x += 250;
  }
  if (inputEvent == act::action::MOVE_DOWN) {
    speed.y += 250;
  }
  if (inputEvent == act::action::MOVE_DOWN) {
    speed.x -= 250;
  }
  if (inputEvent == act::action::FIRE_SECONDARY) {
    fire('missile');
  }
  if (inputEvent == act::action::FIRE_PRIMARY) {
    fire('laser');
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