#include "Missile.h"
#include <cmath>
#include "Sprite.h"

__BEGIN_API

Missile::Missile(Point p, ALLEGRO_COLOR c, Vector s, bool isPlayerShot)
{
   loadSprites();
   centre = p;
   color = c;
   speed = s;
   currentSpriteIndex = 0;
   //colocar angle por fora
   if (isPlayerShot) // Corrige o sprite de míssil
        angle = (atan(speed.y / speed.x) + 4.71) * -1;
   else
        angle = atan(speed.y / speed.x) + 4.71;
   centre = centre + speed * 0.1; // so it doesn't hit its own projectile
}

Missile::~Missile() {
   
}


void Missile::loadSprites()
{
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    Missile::sprites.push_back(std::make_shared<Sprite>("m1.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m2.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m3.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m4.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m5.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m6.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m7.png"));
    Missile::sprites.push_back(std::make_shared<Sprite>("m8.png"));

    al_destroy_path(path);
}

void Missile::update(double dt) {
   

   centre = centre + speed * dt;
   if (!isOutside())
      live = false;
}
bool Missile::isOutside()
{
	if ((centre.x > MainThread::gameWindow->getWidth()) ||
			(centre.x < 0) ||
			(centre.y > MainThread::gameWindow->getHeight()) ||
			(centre.y < 0))
			return true;
  return false;
};
void Missile::draw()
{
    Missile::sprites[currentSpriteIndex]->draw_rotated(centre, this->angle, 0);
    currentSpriteIndex++;
    if (currentSpriteIndex > 7)
        currentSpriteIndex = 0; // Reset o index para acessar o vetor de sprites
}

__END_API