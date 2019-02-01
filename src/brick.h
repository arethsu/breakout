#ifndef BRICK_H
#define BRICK_H

#include <string>
#include <vector>
#include <algorithm>

#include "sprite.h"
#include "ball.h"
#include "powerup.h"

using namespace std;

/** \brief Represents an object on the screen that responds to collisions. */
class Brick : public Sprite
{
 public:
  Brick( int x, int y, int w, int h, int health, bool have_powerup = false );
  ~Brick();

  /** \brief Get the Brick game type. */
  string get_type();

  /** Returns the Powerup. */
  Powerup* get_powerup();

  /** Checks if the brick has a Powerup within it. */
  bool have_powerup();

  /** \brief Get the Brick health. */
  int get_health();

  /** \brief Set the Brick type. */
  void set_type(string t);
  
  /** \biref Set the powerup to nullptr */
  void set_nullptr_powerup();

  /** \brief Set the Brick health. */
  void set_health(int h);

  /** \brief Update the brick type depending on the Brick health. */
  void update_type();

  /** \brief Repell the ball, change type, and set the new health. */
  void collide_ball( Ball* ball );

  /** \brief Check if the brick is dead (i.e. has 0 health). */
  bool is_dead();

 private:
  /** \brief The Brick type. Ex. "RED", "GREEN", "YELLOW", etc.. */
  string type;

  /** \brief The current health. */
  int health;

  /** \brief The Powerup contained within this Brick. */
  Powerup* powerup;

};

#endif
