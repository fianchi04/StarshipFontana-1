#include "SFEvent.h"

/**
 * Effectively wraps an SDL_Event in our custom event type.
 */
SFEvent::SFEvent(const SDL_Event & event) {
  switch (event.type) {
  case SDL_QUIT:
    code = SFEVENT_QUIT;
    break;
  case SDL_USEREVENT:
    code = SFEVENT_UPDATE;
    break;
  case SDL_KEYDOWN: //what keys has been pressed
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      code = SFEVENT_PLAYER_LEFT;
      break;
    case SDLK_RIGHT:
      code = SFEVENT_PLAYER_RIGHT;
      break;
    case SDLK_SPACE:
      code = SFEVENT_FIRE;
      break;
    case SDLK_UP:
      code = SFEVENT_PLAYER_UP;
      break;
    case SDLK_DOWN:
      code = SFEVENT_PLAYER_DOWN;
      break;
    case SDLK_q:
      code = SFEVENT_QUIT;
      break;
    case SDLK_a:
      code = SFEVENT_START;
      break;
    case SDLK_x:  //add key input to drop bonus power: barricades/traps
      code = SFEVENT_BARRICADE;
     break;
    case SDLK_f: //add key input to start over on game over screen
      code = SFEVENT_STARTOVER;
	break;
    }
	break;
  
  case SDL_KEYUP: //what key has been released
    switch (event.key.keysym.sym) {
    case SDLK_LEFT:
      code = SFEVENT_PLAYER_LEFT_UP;
      break;
    case SDLK_RIGHT:
      code = SFEVENT_PLAYER_RIGHT_UP;
      break;
    case SDLK_UP:
      code = SFEVENT_PLAYER_UP_UP;
      break;
    case SDLK_DOWN:
      code = SFEVENT_PLAYER_DOWN_UP;
      break;
    }
    break;
  default:
    code = SFEVENT_NULL;
    break;
  }
}


SFEVENT SFEvent::GetCode() {
  return code;
}
