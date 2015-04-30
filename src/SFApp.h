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
  void    GameOver();
  void    FireProjectile();
  void 	  ScoreDisplay();
  void BarricadeDrop();
  void StartOver();
  bool wall_check;
  void Healthbar();
  void StartScreen();



private:
  bool up = false, down = false, left = false, right = false;
  SDL_Surface           * surface;
//background
  SDL_Texture		* background;
  SDL_Rect back;
  //score display
  SDL_Rect 		score_display;
  //health display
  SDL_Rect		health_bar;

//score counter
  SDL_Texture		* font_image_score;

  bool                    is_running;

  shared_ptr<SFWindow>       sf_window;

  shared_ptr<SFAsset>        player;
  shared_ptr<SFAsset>	     gameover;
  shared_ptr<SFAsset>	     start;
  shared_ptr<SFBoundingBox>  app_box;
  list<shared_ptr<SFAsset> > projectiles;
  list<shared_ptr<SFAsset> > aliens;
  list<shared_ptr<SFAsset> > coins;
  list<shared_ptr<SFAsset> > walls;
  list<shared_ptr<SFAsset> > barricades;
  list<shared_ptr<SFAsset> > lives;

  int fire;
float speed;
int number_of_aliens;
int aliens_alive;
int bonus;
int val;
int alien_death;
bool GO;
int health;
bool BEGIN;
int valb;

//declare digits for score display
SDL_Texture		* d0;
SDL_Texture		* d1;
SDL_Texture		* d2;
SDL_Texture		* d3;
SDL_Texture		* d4;
SDL_Texture		* d5;
SDL_Texture		* d6;
SDL_Texture		* d7;
SDL_Texture		* d8;
SDL_Texture		* d9;

SDL_Texture		* life;




  SFError OnInit();
};
#endif
