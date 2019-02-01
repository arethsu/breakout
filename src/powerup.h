#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <random>
#include "sprite.h"
#include "player.h"
#include "ball.h"
//#include "brick.h"

using namespace std;

/** \brief Represents a power-up that modifies the game in some way. */
class Powerup : public Sprite
{
 public:
  Powerup();
  Powerup( int x, int y, int w, int h );

  /** \brief Returns the game object type. */
  string get_type();

  /** \brief Deactivates the Powerup once it hits the ground. */
  void hit_ground();

  /** \brief Randomizes the an effect, applies it, and deactivates the Powerup. */
  void do_random_effect( Player* player, Ball* ball );

  void update( Player* player, Ball* ball );

  /** \brief Moves the Powerup depending on the speed. */
  void move();

  /** \brief Returns the Powerup's speed. */
  int get_speed();

  /** \brief Returns true if the Powerup is active. */
  bool is_active();

  /** Deactivates the Powerup. */
  void deactivate();

 private:
  int speed;
  bool active;
  string type;
};

#endif
