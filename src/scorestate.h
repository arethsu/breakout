#ifndef SCORESTATE_H
#define SCORESTATE_H

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <regex>

#include "gamestate.h"
#include "menuitem.h"
#include "background.h"

using namespace std;

/** Represents a score screen. */
class ScoreState : public GameState
{

 public:
  ScoreState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures );
  ~ScoreState();

  /** \brief Handles the ScoreState. */
  void run( int& choosen );

  /** \brief Loads the required objects into the `sprites` vector. */
  void load_objects();

  /** \brief Updates all sprites. */
  void load_sprites();

  /** \brief Selects only the textures we need and adds them into a private vector. */
  void filter_textures( map<string, SDL_Texture*>& all_textures );

  /** \brief Moves the selection up. */
  void move_down();

  /** \brief Moves the selection up. */
  void move_up();

  /** \brief Change game screen. */
  void select_current_menu_item( int& choosen );

  /** \brief Sets if the game has been won. */
  void won_the_game( bool won );

  /** \brief Sets if the game has been lost. */
  void lost_the_game( bool lost );

  /** \brief Updates the current score. */
  void update_score( int score );

  /** \brief Returns the current score. */
  int get_score();

  /** Load new score text. */
  void load_score_text();

  /** Hide old score text. */
  void hide_score_text();
 private:
  /** \brief Loads objects, updates their sprites, and adds MenuItems to a the `menu_items` vector. */
  void init();

  SDL_Renderer* renderer;
  bool won_game;
  bool lost_game;
  int score;
  vector<MenuItem*> menu_items;

};

#endif
