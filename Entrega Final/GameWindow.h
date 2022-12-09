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

__BEGIN_API

class GameWindow
{
public:
    GameWindow();
    GameWindow(int width, int height, int fps);
    ~GameWindow();
    void run();

    void setPlayerShip(PlayerShip *playerShip) { _playerShip = playerShip; }
    void setKeyboard(Keyboard *keyBoard) { _keyBoard = keyBoard; }
    void addDrawableItem(Drawable *item) { this->drawableItens.push_front(item); }
    void removeDrawableItem(Drawable *item) { this->drawableItens.remove(item); }

private:
    // Baseado na logica do nosso jogo de poo 2, todos os sprites
    // são adicionados a uma lista para ser desenhado
    std::list<Drawable *> drawableItens;

    // Methods
    void init();
    void draw();
    void loadSprites();
    void drawBackground();
    void updateBackGround(double diffTime);

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