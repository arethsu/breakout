#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <vector>
#include <map>
#include <string>

#include "gamestate.h"
#include "menuitem.h"

using namespace std;

/** \brief Represents a menu, a type of selection screen. */
class MenuState : public GameState
{

 public:
  MenuState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures );
  ~MenuState();

  /** \brief Handles the MenuState. */
  void run( int& choosen );

  /** \brief Loads the required MenuItem sprites into the `menu_items` vector. */
  void load_objects();

  /** \brief Updates/loads the MenuItem textures. */
  void load_sprites();

  /** \brief Selects only the textures we need and adds them into a private vector. */
  void filter_textures( map<string, SDL_Texture*>& all_textures );

  /** \brief Switches selected item. */
  void move_down();

  /** \brief Switches selected item. */
  void move_up();

  /** Switch to another GameState depending on which item is selected. */
  void select_current_menu_item( int& choosen );

 private:
  /** \brief Loads MenuItems, updates their sprites, and adds them to a the `menu_items` vector. */
  void init();

  SDL_Renderer* renderer;
  vector<MenuItem*> menu_items;

};

#endif
