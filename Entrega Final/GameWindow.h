#ifndef GameWindow_h
#define GameWindow_h

#include <allegro5/allegro.h>
#include <memory>
#include <string>
#include <stdio.h>
#include <list> // Implementação de Lista ligada
#include "Threads/thread.h"
#include "Threads/traits.h"

#include "PlayerShip.h"
#include "KeyBoard.h"
#include "Sprite.h"
#include "Vector.h"
#include "Drawable.h"
#include "Enemy.h"
#include "Projectile.h"

__BEGIN_API

class GameWindow
{
public:
    GameWindow();
    GameWindow(int width, int height, int fps);
    ~GameWindow();
    void run();

    bool getFinish() { return _finish; }
    void setFinish(bool condition) { this->_finish = condition; }
    void setPlayerShip(PlayerShip *playerShip) { _playerShip = playerShip; }
    void setKeyboard(Keyboard *keyBoard) { _keyBoard = keyBoard; }
    void getEnemyList() { return enemies; }
    void pushEnemyList(Enemy *enemy) { this->enemies.push_front(enemy); }
    void removeEnemyList(Enemy *enemy) { this->enemies.remove(enemy); }
    void pushProjectileList(Projectile *projectile) { this->projectile.push_front(projectile); }
    void removeProjectileList(Projectile *projectile) { this->projectile.remove(projectile); }

private:
    

    std::list<Enemy *> enemies;
    std::list<Projectile *> projectiles;

    // Methods
    void init();
    void draw();
    void loadSprites();
    void drawBackground();
    void updateBackGround(double diffTime);

    bool _finish;
    
    // Window variables
    int _displayWidth;
    int _displayHeight;
    int _fps;

    // Game object
    PlayerShip *_playerShip;
    Keyboard *_keyBoard;

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