#ifndef SFAPP_H
#define SFAPP_H

#include <memory>   // Pull in std::shared_ptr
#include <iostream> // Pull in std::cerr, std::endl
#include <list>     // Pull in list
#include <sstream>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

#include <SDL2/SDL_ttf.h> //sdl font library
/**
 * Represents the StarshipFontana application.  It has responsibilities for
 * * Creating and destroying the app window
 * * Processing game events
 */
class SFApp {
public:
  SFApp(std::shared_ptr<SFWindow>);
  virtual ~SFApp();
  void    OnEvent(SFEvent &);
  int     OnExecute();
  void    OnUpdateWorld();
  void    OnRender();

  void    FireProjectile();
  void BarricadeDrop();
  bool wall_check;
private:
  bool up = false, down = false, left = false, right = false;
  SDL_Surface           * surface;
//background
  SDL_Texture		* background;
  SDL_Rect back;

//score counter
  SDL_Texture		* font_image_score;

  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > barricades;

  int fire;
float speed;
int number_of_aliens;
int aliens_alive;
int bonus;
int val;
int alien_death;



  SFError OnInit();
};
#endif
