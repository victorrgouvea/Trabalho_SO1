#include "Engine.h"

__BEGIN_API


Engine::Engine() {}

Engine::~Engine() {}

void Engine::setGameWindow(GameWindow *gameWindow) {
   this->gameWindow = gameWindow;
}

void Engine::setPlayer(Player *player) {
   this->player = player;
}

void Engine::run() {
   while (gameWindow->getFinish() != false) {
      playerCollisionCheck();  // checa se o player foi atingido por alguma coisa
      enemyCollisionCheck();  // checa se algum inimigo foram atingidos pelo player
      objectsClean();
      Thread::yield();
   }
}

void Engine::playerCollisionCheck() { 
   for (auto proj = enemiesProj.begin(); proj != enemiesProj.end();)
    {
        Projectile *projectile = *proj;
        proj++;

        if (playerHitCheck(projectile, player))
        {
            player->hit();
            // Destrói o tiro
            gameWindow->removeDrawableItem(projectile);
            enemiesProj.remove(projectile);
            delete projectile;

            if (player->isDead())
            {
                gameWindow->setFinish(true);
                return;
            }
        }
    }
}

void Engine::enemyCollisionCheck() {
   for (auto proj = playerProj.begin(); proj != playerProj.end();)
    {
        Projectile *projectile = *proj;
        proj++;

        for (auto obj = gameWindow->getEnemyList().begin(); obj != gameWindow->getEnemyList().end();)
        {
            Enemy *enemy = *obj;
            obj++;

            if (enemyHitCheck(projectile, enemy))
            {
                gameWindow->removeDrawableItem(projectile);
                playerProj.remove(projectile);
                delete playerProj;

                enemy->hit();
                if (enemy->isDead())
                {
                    gameWindow->removeDrawableItem(enemy);
                    gameWindow->getEnemyList().remove(enemy);
                    delete enemy;
                }
            }
        }
    }
}

bool Engine::playerHitCheck(Projectile *projectile, Player *player) {
   int tamanhoPlayer = player->getSize();
   Point posicaoProjectile = projectile->getPosition();
   Point posicaoPlayer = player->getPosition();

   if (posicaoProjectile.x > posicaoPlayer.x - tamanhoPlayer &&
        (posicaoProjectile.x < posicaoPlayer.x + tamanhoPlayer) &&
        (posicaoProjectile.y > posicaoPlayer.y - tamanhoPlayer) &&
        (posicaoProjectile.y < posicaoPlayer.y + tamanhoPlayer))
      return true;
   return false;
}

bool Engine::enemyHitCheck(Projectile *projectile, Enemy *enemy) {
   int tamanhoEnemy = enemy->getSize();
   Point posicaoProjectile = projectile->getPosition();
   Point posicaoEnemy = enemy->getPosition();

   if (posicaoProjectile.x > posicaoEnemy.x - tamanhoEnemy &&
        (posicaoProjectile.x < posicaoEnemy.x + tamanhoEnemy) &&
        (posicaoProjectile.y > posicaoEnemy.y - tamanhoEnemy) &&
        (posicaoProjectile.y < posicaoEnemy.y + tamanhoEnemy))
      return true;
   return false;
}


/*
Engine::Engine(int w, int h, int fps) : _displayWidth(w), _displayHeight(h), 
					_fps(fps),
					_timer(NULL),
					_eventQueue(NULL),
               _finish(false)
{
   
}

Engine::~Engine() {
   if (_timer != NULL) al_destroy_timer(_timer);
   if (_eventQueue != NULL) al_destroy_event_queue(_eventQueue);
   if (_display != NULL) al_destroy_display(_display);

   bg.reset();
   spaceShip.reset();

}


// initialize Allegro, the _display window, the addons, the timers, and event 
// sources
void Engine::init() {
   // initialize allegro
   al_init();
   // create the display
   if ((_display = al_create_display(_displayWidth, _displayHeight)) == NULL) {
      std::cout << "Cannot initialize the display\n";
      exit(1); 
   }   
   // initialize addons
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   // initialize our timers
   if ((_timer = al_create_timer(1.0 / _fps)) == NULL) {
      std::cout << "error, could not create timer\n";
      exit(1);
   }
   if ((_eventQueue = al_create_event_queue()) == NULL) {
      std::cout << "error, could not create event queue\n";
      exit(1);
   }
   // register our allegro _eventQueue
   al_register_event_source(_eventQueue, al_get_display_event_source(_display)); 
   al_register_event_source(_eventQueue, al_get_timer_event_source(_timer));
   al_start_timer(_timer);
   // install keyboard
   if (!al_install_keyboard()) {
      std::cerr << "Could not install keyboard\n";
   }
   
   // register keyboard
   al_register_event_source(_eventQueue, al_get_keyboard_event_source());

   loadSprites();
}


// repeatedly call the state manager function until the _state is EXIT
void Engine::run() {
   float prevTime = 0;
   init()
   // main engine loop
   while (!_finish) {
      gameLoop(prevTime);
   }
}

void Engine::gameLoop(float& prevTime) {
   ALLEGRO_EVENT event;
   ALLEGRO_KEYBOARD_STATE kb;
   bool redraw = true;
   float crtTime;
   
   // input
   al_get_keyboard_state(&kb);      
   input(kb); //irá retornar uma tecla de ação. TODO: necessário transformar em Thread e fazer a ação
   
   // get event
   al_wait_for_event(_eventQueue, &event);
   
   // _display closes
   if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      _finish = true;
      return;
   }
   
   // timer
   if (event.type == ALLEGRO_EVENT_TIMER) {
      crtTime = al_current_time();
      update(crtTime - prevTime);
      prevTime = crtTime;
      redraw = true;
   }
   
   // render
   if (redraw && al_is_event_queue_empty(_eventQueue)) {
      redraw = false;      
      draw(); 
      al_flip_display();
   }
}


  return act::action::NO_ACTION;
}
// update the game mode
void Engine::update(double dt) {
   //Spaceship
   centre = centre + speed * dt;
   selectShipAnimation(); // must happen before we reset our speed
   speed = Vector(0, 0); // reset our speed
   checkBoundary();

   // background
   bgMid = bgMid + bgSpeed * dt;   
   if (bgMid.x >= 800) {
      bgMid.x = 0;
   }
}

// draws for the game mode
void Engine::draw() {   
   drawBackground();
   drawShip(spaceShip, 0);
}


void Engine::checkBoundary() {   
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



void Engine::drawShip(std::shared_ptr<Sprite> sprite, int flags) {   
   sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
}
void Engine::drawBackground() {
   bg->draw_parallax_background(bgMid.x, 0);
}




void Engine::selectShipAnimation() {
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

void Engine::loadSprites()
{
   // Create Ship
   centre = Point(215, 245);
   color= al_map_rgb(0, 200, 0);

   // represents the middle of the image width-wise, and top height-wise
   bgMid = Point(0, 0);
   fgMid = Point(800, 0);
   fg2Mid= Point(300, 300);
   bgSpeed = Vector(50, 0);
   fgSpeed = Vector(-90, 0);

   // Go to resources directory
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));   
   // sprites
   spaceShip = std::make_shared<Sprite> ("Sprite2.png"); //espaçonave do usuário
   bg = std::make_shared<Sprite> ("BGstars.png"); //fundo da tela - background
   // delete path 
   al_destroy_path(path);

}
*/
__END_API
