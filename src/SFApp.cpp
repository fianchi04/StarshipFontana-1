#include "SFApp.h"
#include "SFAsset.h"
SFApp::SFApp(std::shared_ptr<SFWindow> window) : fire(0), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);


  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w, 88.0f); //add the player to the screen
  player->SetPosition(player_pos);

   //render first ten aliens on screen
  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens) * i, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
 	 }



//load textures for images for score display
d0 = IMG_LoadTexture(sf_window->getRenderer(), "assets/0.png");
d1 = IMG_LoadTexture(sf_window->getRenderer(), "assets/1.png");
d2 = IMG_LoadTexture(sf_window->getRenderer(), "assets/2.png");
d3 = IMG_LoadTexture(sf_window->getRenderer(), "assets/3.png");
d4 = IMG_LoadTexture(sf_window->getRenderer(), "assets/4.png");
d5 = IMG_LoadTexture(sf_window->getRenderer(), "assets/5.png");
d6 = IMG_LoadTexture(sf_window->getRenderer(), "assets/6.png");
d7 = IMG_LoadTexture(sf_window->getRenderer(), "assets/7.png");
d8 = IMG_LoadTexture(sf_window->getRenderer(), "assets/8.png");
d9 = IMG_LoadTexture(sf_window->getRenderer(), "assets/9.png");
score_display.w = 30; //set score display dimension and coordinates
score_display.h = 60;
score_display.x = 265;
score_display.y = 10;

//load textures for health bar
life = IMG_LoadTexture(sf_window->getRenderer(), "assets/health.png");
health_bar.w = 30;
health_bar.h = 30;
health_bar.x = 10;
health_bar.y = 40;

  val = 0;

alien_death = 00000; //counter for how many aliens killed by player
  
 

 //place five blocks/walls
  	for(int i=0; i<5; i++) {
   	 // place a wall at 100 * i
   		 auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
    		auto pos   = Point2((200) * i, 200.0f);
    		wall->SetPosition(pos);
    		walls.push_back(wall);
  	}


//set background
back.x= 0;
back.y = 0;
back.w = 640;
back.h = 480;
background = IMG_LoadTexture(sf_window->getRenderer(), "assets/background.jpeg");

  }
  
 
  
  
  


  

  
  
SFApp::~SFApp() {
}
//player keyboard input
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
  case SFEVENT_STARTOVER: //code for restarting the game (from game over screen)
   StartOver();
    break;
  case SFEVENT_START: //code for starting the game
   BEGIN = false;
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
    if ((bonus- 300)/25 > 3){ //drop a barricade (trap) if player has collected enough coins
    BarricadeDrop();
    bonus = bonus -50;} // ???????????????????????? change counter
    break;
  }
}






void SFApp::StartOver(){ //on start up reset counters to 0 and reset player positions
	GO = false;
//kill everything on screen
for (auto a : aliens){
	a->HandleCollision();}
for (auto p : projectiles){
	p->HandleCollision();}
for (auto b : barricades){
	b->HandleCollision();}
for (auto c : coins){
	c->HandleCollision();}
player ->HandleCollision();

	  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w, 88.0f);
  player->SetPosition(player_pos);

  //render first ten aliens on screen
  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2((canvas_w/number_of_aliens) * i, 400.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
 	 }

  health = 5;
  val = 0;
  alien_death = 000000;
  valb = 0;
}
	

void SFApp::StartScreen(){
//Start screen interface
	
	cout<< "Welcome" << endl;
	
	//render the start screen image
    start = make_shared<SFAsset>(SFASSET_START, sf_window);
    auto pos   = Point2(320, 240);
    start->SetPosition(pos);

    if (!BEGIN){StartOver();}
	
}





void SFApp::GameOver(){
//method to 'end' the game under certain conditions
	
	cout<< "Game Over" << endl;
	
	//render the game over screen image
    gameover  = make_shared<SFAsset>(SFASSET_GAMEOVER, sf_window);
    auto pos   = Point2(320, 240);
    gameover->SetPosition(pos);
}





int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  bonus = 0; //counters on start up
  health = 5;
  alien_death = 00000;
  wall_check = false;
  GO = false;
  BEGIN= true; 
  StartScreen();//initiate start screen image first
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}











void SFApp::OnUpdateWorld() {

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

  //coins drop south
  for(auto c: coins) {
    c->GoSouth(5.0f);
  }
 
  //lives drop south
  for(auto l: lives) {
    l->GoSouth(5.0f);
  }

  // Update enemy positions
  for(auto a : aliens) {
    a->GoSouth(rand()%2); //aliens moving south at different speeds
  }

  // Detect collisions aliens with projectiles
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
        p->HandleCollision();
        a->HandleCollision();
	alien_death++;
        //working reward spawn on alien death
        valb = rand()% 16 + 1; // 1 in 15 chance of getting a health power up that will give full health back
	if(valb == 3){
		auto nlife = make_shared<SFAsset>(SFASSET_NLIFE, sf_window);
  		auto gPos = a->GetPosition(); 
  		//get the position of the alien collided with
 		 nlife->SetPosition(gPos);
 	 	lives.push_back(nlife);
	}
	else {
        	auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
  		auto gPos = a->GetPosition(); 
  		//get the position of the alien collided with
 	 	coin->SetPosition(gPos);
 		 coins.push_back(coin);}
	}
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
	cout << "Coins: " << endl; //???????????????????????
      cout << bonus << endl;
      
    }
    
    // Detect player picking up lives
    for(auto l : lives) {
      if(player->CollidesWith(l)) {
        l->HandleCollision();
        health = 5;}  
    }


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

	  
    
  //detect aliens colliding with player (game over)
    for (auto a : aliens){
    	if(a->CollidesWith(player)){
    	   a->HandleCollision();
    	   player->HandleCollision();
	health= health -1;
	if(health<0){
		cout << "Game over! Player dead!"<< endl;
		GO = true;
		GameOver();}
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

  for (auto l : lives){
   if(l->IsAlive()){l->OnRender();}
  }
   
  for (auto b: barricades){
  if(b->IsAlive()){b-> OnRender();}
  }
  
   if (GO){ //render the gameover image screen last so that it will be on top of the sprites, this saves having to 'kill' all the sprites on screen during game over
  gameover->OnRender();}

  if(BEGIN){
  start->OnRender();}

  ScoreDisplay();
  Healthbar();

  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}



void SFApp::Healthbar(){
	for(int i = 0; i < health; i++){
		SDL_RenderCopy(sf_window->getRenderer(), life, NULL, &health_bar);
		health_bar.x+= 30;
	}
	health_bar.x = 10; //reset to first x coord ready for repeat
}




void SFApp::ScoreDisplay() {

	int tmp = 0;

	string dig = std::to_string(alien_death);
	for(int i = 0; i <5 ; i++){ //score will be displayed as five digit number
		if (dig.length() - 1 < 4- i){
			SDL_RenderCopy(sf_window->getRenderer(), d0, NULL, &score_display);
			tmp++; //tmp counts how many 0s will be before the score (e.g. 00045)
		}		 
		else if(dig.length()>0){
			switch(dig.at(i - tmp)){
				case '0' : 
					SDL_RenderCopy(sf_window->getRenderer(), d0, NULL, &score_display);
					break;
				case '1' : 
					SDL_RenderCopy(sf_window->getRenderer(), d1, NULL, &score_display);
					break;
				case '2' : 
					SDL_RenderCopy(sf_window->getRenderer(), d2, NULL, &score_display);
					break;
				case '3' : 
					SDL_RenderCopy(sf_window->getRenderer(), d3, NULL, &score_display);
					break;
				case '4' : 
					SDL_RenderCopy(sf_window->getRenderer(), d4, NULL, &score_display);
					break;
				case '5' : 
					SDL_RenderCopy(sf_window->getRenderer(), d5, NULL, &score_display);
					break;
				case '6' : 
					SDL_RenderCopy(sf_window->getRenderer(), d6, NULL, &score_display);
					break;
				case '7' : 
					SDL_RenderCopy(sf_window->getRenderer(), d7, NULL, &score_display);
					break;
				case '8' : 
					SDL_RenderCopy(sf_window->getRenderer(), d8, NULL, &score_display);
					break;
				case '9' : 
					SDL_RenderCopy(sf_window->getRenderer(), d9, NULL, &score_display);
					break;
			}		
		}
		score_display.x += 30; //digit images at 30px wide so must be +30 on x coord
	}
	score_display.x = 265; //reset to the first x coord of first digit ready to reloop
}


//allow player to drop barricade power ups
void SFApp::BarricadeDrop() { //int y is bonus points collected
  //int times = y/30;
  auto bd = make_shared<SFAsset>(SFASSET_BARRICADE, sf_window);
  auto x  = player->GetPosition();
  bd->SetPosition(x);
  barricades.push_back(bd);
}




void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
