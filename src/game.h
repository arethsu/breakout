#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <map>

#include "gamestate.h"
#include "playstate.h"
#include "menustate.h"
#include "scorestate.h"

#include "sprite.h"

class Game
{
 public:
  Game();

  /** \brief The main game loop. */
  void run();

 private:
  /** \brief Loads a texture from file. */
  SDL_Texture* load_texture( const char* filename );

  /** \brief Loads the game textures. */
  void load_textures();

  /** \brief Configures SDL. */
  void sdl_settings();

  SDL_Window* window;
  SDL_Renderer* renderer;
  map<string, SDL_Texture*> textures;

};

#endif
