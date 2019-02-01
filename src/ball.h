#ifndef BALL_H
#define BALL_H

#include <string>

#include "sprite.h"
#include "player.h"

using namespace std;

/** \brief Represents a bouncing object that destorys bricks on collision. */
class Ball : public Sprite
{
 public:
  Ball( int x, int y, int w, int h );

  /** \brief Move the ball. */
  void move();
  
  /** \brief Get the game object type. */
  string get_type();

  /** \brief Changes direction of the ball once it "bounces" on a wall. */
  void bounce_walls();

  /** \brief Bounces the Ball off the Player once it collides with them. */
  void collide_player( Player* player );

  /** \brief Handles when the Ball hits the ground. */
  void hit_ground( Player* player, int& choosen );

  /** \brief Set the Ball speed. */
  void set_speed( int speed );

  /** \brief Set the X modifier. */
  void set_modifierX( double modX );

  /** \brief Set the Y modifier. */
  void set_modifierY( double modY );

  /** \brief Get the Ball speed. */
  int get_speed();

  /** \brief Get the X modifier. */
  double get_modifierX();

  /** \brief Get the Y modifier. */
  double get_modifierY();

 private:
  /** \brief The Ball X modifier (Ball direction). */
  double modifierX;

  /** \brief The Ball Y modifier (Ball direction). */
  double modifierY;

  /** \brief The Ball speed. */
  int speed;
};

#endif
