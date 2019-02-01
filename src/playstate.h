#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include <map>
#include <string>

#include "gamestate.h"
#include "ball.h"
#include "brick.h"
#include "player.h"
#include "heart.h"

using namespace std;

/** \brief Represents a game screen. */
class PlayState : public GameState
{

 public:
  PlayState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures );
  ~PlayState();

  /** \brief Handles the PlayState. */
  void run( int& choosen );

  /** \brief Loads the current level (all bricks) into the `sprites` vector. */
  void load_objects();

  /** \brief Loads the ball, the player, and the heart sprite. */
  void load_important_objects();

  /** \brief Deletes bricks and powerups from the `sprites` vector. */
  void delete_bricks();

  /** \brief Load/updates all sprites. */
  void load_sprites();

  /** \brief Switches level. */
  void level( int level );

  /** \brief Returns `true` if the Player has won the game. */
  bool have_won_the_game();

  /** \brief Returns `true` if the Player has lost the game. */
  bool have_lost_the_game();

  /** \brief Selects only the textures we need and adds them to a private vector. */
  void filter_textures( map<string, SDL_Texture*>& all_textures );

  /** \brief Resets the Ball and Player position. */
  void reset_ball_and_player_position();

  /** \brief Returns the current score. */
  int get_score();

 private:
  void init();

  Ball* ball;
  Player* player;
  Heart* heart;
  vector<Brick*> bricks;
  SDL_Renderer* renderer;

  int current_level;
  bool won_game;
  bool lost_game;
  int score;

};

#endif
