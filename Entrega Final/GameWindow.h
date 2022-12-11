#ifndef GameWindow_h
#define GameWindow_h

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <stdio.h>
#include <list> // Implementação de Lista ligada
#include "thread.h"
#include "traits.h"

#include "Player.h"
#include "GameInput.h"
#include "Sprite.h"
#include "Vector.h"
#include "Drawable.h"
#include "Enemy.h"
#include "Projectile.h"

__BEGIN_API

class GameWindow
{
public:
    GameWindow(int width, int height, int fps) : _displayWidth(width), _displayHeight(height), _fps(fps) {init();};
    ~GameWindow();
    void run();
    bool getGameRunning() {return isGameRunning;}
    void setGameRunning(bool valor) {isGameRunning = valor;}
    std::list<Drawable *> getSpriteList() { return spriteToDraw; }
    void drawLives();
    void drawSprite();
    // Por algum motivo o compilador não deixa definir elas no ,cc
    void addSprite(Drawable *sprt)
    {
        spriteToDraw.push_front(sprt);
    }       
    void removeSprite(Drawable *sprt)
    { 
        spriteToDraw.remove(sprt); 
    }
    int getWidth() {return _displayWidth;}
    int getHeight() {return _displayHeight;}
private:
    // Methods
    std::list<Drawable *> spriteToDraw;
    void init();
    void drawEnemy();
    void drawProject();
    void loadSprites();
    void drawBackground();
    void updateBackGround(double diffTime);

    bool eraseData;
    // Window variables
    int _displayWidth;
    int _displayHeight;
    int _fps;
    bool isGameRunning;
    // Time variables
    float previousTime;

    // Background
    Point bgMid; /**<point used by the background to draw from */
    Point fgMid;
    Point fg2Mid;
    Vector bgSpeed; /**<background movement speed */
    Vector fgSpeed;
    std::shared_ptr<Sprite> bgSprite; /**<shared pointer to background animation */
    std::shared_ptr<Sprite> fgSprite;

    // Allegro objects
    ALLEGRO_TIMER *_timer;
    ALLEGRO_EVENT_QUEUE *_eventQueue;
    ALLEGRO_DISPLAY *_display;
};

__END_API

#endif