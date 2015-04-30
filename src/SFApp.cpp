#include "SFApp.h"
#include "SFAsset.h"
#include <SDL2/SDL_ttf.h>
SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w, 88.0f);
  player->SetPosition(player_pos);

  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens) * i, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);

 	 }


  int val = 0;
int alien_death;
  
  //check that wall spawn works

 
  	for(int i=0; i<5; i++) {
   	 // place a wall at 100 * i
   		 auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
    		auto pos   = Point2((200) * i, 200.0f);
    		wall->SetPosition(pos);
    		walls.push_back(wall);
  	}

  	
  	
//check that barricades are visible
	/*for(int i=0; i<5; i++) {
   	 // place a barricade at 30 * i
   		 auto barricade = make_shared<SFAsset>(SFASSET_BARRICADE, sf_window);
    		auto pos   = Point2((50) * i, 50.0f);
    		barricade->SetPosition(pos);
    		barricades.push_back(barricade);
    		cout << "test" << endl;*/
  	//}
  
  

//this code makes a coin and making point 2 (x and y coordinate), and putting it in that place (pos)
/*
  auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  auto pos  = Point2((canvas_w/4), 100);
  coin->SetPosition(pos);
  coins.push_back(coin);
  //push back is adding it to a list/array of coins
  //need to look up push back, it's a part of c++
  // for coin spawn, instead of auto pos, do a: get position to find alien coord*/


//set background
back.x= 0;
back.y = 0;
back.w = 640;
back.h = 480;
background = IMG_LoadTexture(sf_window->getRenderer(), "assets/background.jpeg");

// Font names
string fonts[] = {"Lato-Reg.TTF", "FFFFORWA.TTF"};

  }
  
 
  
  
  
  
  
  
SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    left = true;
    break;
  case SFEVENT_PLAYER_RIGHT:
    right = true;
    break;
  case SFEVENT_PLAYER_UP:
    up = true;
    break;
  case SFEVENT_PLAYER_DOWN:
    down = true;
    break;
  case SFEVENT_FIRE:
     fire ++;
    FireProjectile();;
    break;

  case SFEVENT_PLAYER_LEFT_UP:
   left = false;
    break;
  case SFEVENT_PLAYER_RIGHT_UP:
   right = false;
    break;
  case SFEVENT_PLAYER_UP_UP:
    up  = false;
    break;
  case SFEVENT_PLAYER_DOWN_UP:
    down = false;
    break;

  case SFEVENT_BARRICADE:
    if ((bonus- 300)/25 > 3){ //drop a barricade if player has collected enough coins
    BarricadeDrop();
    bonus = bonus -50;}
    break;
  }
}







int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
 }
  int invasion = 0;
  alien_death = 0;
  int bonus = 0;
  bool wall_check = false;
}








void SFApp::OnUpdateWorld() {

//show score
	//font_image_score = renderText(to_string(alien_death), "Lato-Reg.TTF", 24);

  //boolean statements allowing player movement in multiple directions at the same time
  if(left){
    player->GoWest();
	for( auto w : walls){ //checks to see if there is a wall collision, if there is then it 'undos' the move in the desired direction.
	   if(player->CollidesWith(w)){
		player->GoEast();}
	}

  }
  if (right){
    player->GoEast();
	for( auto w : walls){
	   if(player->CollidesWith(w)){
		player->GoWest();}
	}
  }
  if (up){
    player->GoNorth();
	for( auto w : walls){
	   if(player->CollidesWith(w)){
		player->GoSouth(8.0f);}
	}
  }
  if (down){
    player->GoSouth(8.0f);
	for( auto w : walls){
	   if(player->CollidesWith(w)){
		player->GoNorth();}
	}
  }



  // Update projectile positions
  
  for(auto p: projectiles) {
    p->GoNorth();
  }

  for(auto c: coins) {
    c->GoSouth(5.0f);
  }

  //make walls move down the screen
  //for (auto w: walls){
   // w->GoSouth(3.0f);
  //}

  // Update enemy positions
  for(auto a : aliens) {
    a->GoSouth(rand()%2); //aliens moving slowly south
  }

  // Detect collisions aliens with projectiles
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        p->HandleCollision();
        a->HandleCollision();
	alien_death++;
        //working coin spawn on alien death
        auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  	auto gPos = a->GetPosition(); 
  	//get the position of the alien collided with
 	 coin->SetPosition(gPos);
 	 coins.push_back(coin);}
   	 }
 	}
  

  //working implementation of new alien spawn
 int aliens_alive = 0; //int to count how many aliens are living
 for(auto a : aliens) {
      if(a->IsAlive()) {//counts aliens present at each render
      	aliens_alive++;
      	}
  }
  for (aliens_alive; aliens_alive< 10; aliens_alive++)
  { //if one alien has been killed, there will be less than 10 present so new aliens will be generated until the required amount are there
   	auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
   	 auto aPos   = Point2(rand()%640, 480);
   	 alien->SetPosition(aPos);
   	 aliens.push_back(alien);
  }
  
  
  
  // Detect player picking up coins
    for(auto c : coins) {
      if(player->CollidesWith(c)) {
        c->HandleCollision();
        bonus++;}
	cout << "Coins: " << endl;
      cout << bonus << endl;
      
    }
    

//detect player collisions with walls
   for (auto w : walls)
     { if (player->CollidesWith(w)){wall_check = true;}}
//stop projectiles going through walls
   for (auto w : walls){
	for (auto p : projectiles){
         if (p->CollidesWith(w)){
	   p->HandleCollision();}
	}
   }
	   


    //detect aliens colliding with barricades
   for (auto b : barricades){
    for (auto a : aliens){
    	if(a->CollidesWith(b)){
    	   a->HandleCollision();
    	   b->HandleCollision();
	   alien_death++;}
    	   }
   }

  //detect aliens colliding with walls
  for (auto w : walls){
   for (auto a: aliens){
	if(a->CollidesWith(w)){
		val = rand () % -1, 2;
		if (val == 0){a->GoEast();}
		if (val == 1){a->GoWest();}
		}
	}
}

	  
    
  //detect aliens colliding with aliens (game over)
    for (auto a : aliens){
    	if(a->CollidesWith(player)){
    	   a->HandleCollision();
    	   player->HandleCollision();
	cout << "Game over! Player dead!"<< endl;
	//GameOver();
	}
    	   }
   


  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);


//remove invisible projectiles
list<shared_ptr<SFAsset>> tmpb;
  	for(auto p : projectiles) {
           if(p->IsAlive()) {
    	   tmpb.push_back(p);
    			}
  	    }
    projectiles.clear();
    projectiles = list<shared_ptr<SFAsset>>(tmpb);
   
    
    
    
//remove dead barricades
list<shared_ptr<SFAsset>> tmpc;
  	for(auto b : barricades) {
           if(b->IsAlive()) {
    	   tmpc.push_back(b);
    			}
  	    }
    barricades.clear();
    barricades = list<shared_ptr<SFAsset>>(tmpc);
}












void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  //background
  SDL_RenderCopy(sf_window->getRenderer(), background, NULL, &back);

  // draw the player
  player->OnRender();

  for(auto w: walls){
  w->OnRender();
  }
  
  
  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto c: coins) {
   if(c->IsAlive()){c->OnRender();}
   }
   
  for (auto b: barricades){
  if(b->IsAlive()){b-> OnRender();}
  }
  
  

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}





//allow player to drop barricade power ups
void SFApp::BarricadeDrop() { //int y is bonus points collected
  //int times = y/30;
  auto bd = make_shared<SFAsset>(SFASSET_BARRICADE, sf_window);
  auto x  = player->GetPosition();
  bd->SetPosition(x);
  barricades.push_back(bd);
  //times= times - 1;
 // y = times*30;
  //return y;
}




void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
