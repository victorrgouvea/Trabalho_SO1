#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "GameWindow.h"


__BEGIN_API

GameWindow::~GameWindow()
{
     if (_timer != NULL)
         al_destroy_timer(_timer);
     if (_eventQueue != NULL)
         al_destroy_event_queue(_eventQueue);
     if (_display != NULL)
         al_destroy_display(_display);

     bgSprite.reset();
}

void GameWindow::run()
{
    
    init();
    while (isGameRunning)
    {
        if (MainThread::player== nullptr)
        {
            Thread::yield();
            continue;
        }
        ALLEGRO_EVENT event;
        al_wait_for_event(_eventQueue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            eraseData = true;
            return;
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
            drawLives();
            drawEnemy();
            //drawProject();
            Thread::yield();
        }
}

void GameWindow::drawLives() {
   Point centre(_displayWidth-70, _displayWidth-50);
   if (MainThread::player->getLives() > 0) {
	  al_draw_rectangle(_displayWidth - 70, 50, _displayWidth - 50, 70,
			    al_map_rgb(0, 255, 0), 5);
   }
   if (MainThread::player->getLives()  > 1) {
      al_draw_rectangle(_displayWidth - 110, 50, _displayWidth - 90, 70,
			al_map_rgb(0, 255, 0), 5);
   }
   if (MainThread::player->getLives()  > 2) {
      al_draw_rectangle(_displayWidth - 150, 50, _displayWidth - 130, 70,
			al_map_rgb(0, 255, 0) , 5);
   } 
}
void GameWindow::drawEnemy()
{
    if (al_is_event_queue_empty(_eventQueue))
    {
        float timeNow = al_current_time();
        double newTime = timeNow - previousTime;
        previousTime = timeNow;
        updateBackGround(newTime);
        bgSprite->draw_parallax_background(bgMid.x, 0);

        if (MainThread::player!= nullptr)
        {
            MainThread::player->update(newTime);
            MainThread::player->draw();
        }

        for (auto iter = enemyToDraw.begin(); iter != enemyToDraw.end();)
        {
            
            Drawable *item = *iter;
            iter++;
            item->update(newTime);
            item->draw();
        }

        for (auto iter = projectToDraw.begin(); iter != projectToDraw.end();)
        {
            Drawable *item = *iter;
            iter++;
            item->update(newTime);
            item->draw();
        }

        al_flip_display();
    }
}

void GameWindow::drawProject()
{
    if (al_is_event_queue_empty(_eventQueue))
    {
        float currentTime = al_current_time();
        double diffTime = currentTime - previousTime;
        previousTime = currentTime;
        updateBackGround(diffTime);
        bgSprite->draw_parallax_background(bgMid.x, 0);

        if (MainThread::player!= nullptr)
        {
            MainThread::player->update(diffTime);
            MainThread::player->draw();
        }
        al_flip_display();
    }
}


void GameWindow::updateBackGround(double dt)
{
    bgMid = bgMid + bgSpeed * dt;
    if (bgMid.x >= 800)
        bgMid.x = 0;
}

void GameWindow::drawBackground() {  }

void GameWindow::init()
{
    db<GameWindow>(TRC) << "GameWindow Init started\n";
    // initialize allegro
    al_init();

    // create the display
    if ((this->_display = al_create_display(this->_displayWidth, this->_displayHeight)) == NULL)
    {
        std::cout << "Cannot initialize the display\n";
        exit(1);
    }

    // initialize addons
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    // initialize our timers
    if ((_timer = al_create_timer(1.0 / _fps)) == NULL)
    {
        std::cout << "error, could not create timer\n";
        exit(1);
    }

    if ((this->_eventQueue = al_create_event_queue()) == NULL)
    {
        std::cout << "error, could not create event queue\n";
        exit(1);
    }

    // register our allegro _eventQueue
    al_register_event_source(_eventQueue, al_get_display_event_source(_display));
    al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
    al_start_timer(_timer);

    loadSprites();
}

void GameWindow::loadSprites()
{
    // represents the middle of the image width-wise, and top height-wise
    bgMid = Point(0, 0);
    fgMid = Point(800, 0);
    fg2Mid = Point(300, 300);
    bgSpeed = Vector(50, 0);
    fgSpeed = Vector(-90, 0);
    isGameRunning = true;
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    // sprites
    bgSprite = std::make_shared<Sprite>("BGstars.png"); // fundo da tela - background

    // delete path
    al_destroy_path(path);
}

__END_API