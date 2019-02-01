#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <map>

#include "sprite.h"

using namespace std;

class GameState
{
 public:
  virtual ~GameState(){};
  virtual void run( int& choosen ) = 0;
  virtual void load_objects() = 0;
  virtual void load_sprites() = 0;
  virtual void filter_textures( map<string, SDL_Texture*>& all_textures ) = 0;
 protected:
  virtual void init() = 0;
  vector<Sprite*> sprites;
  map<string, SDL_Texture*> textures;
};

#endif
