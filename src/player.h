#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "sprite.h"

using namespace std;

/** \brief Represents a user playing the game. */
class Player : public Sprite
{

 public:
  Player( int x, int y, int w, int h );

   /** \brief Moves the Player while constricting him to the game screen. */
  void move( const Uint8* key );

  /** \brief Get the object type. */
  string get_type();

  /** \brief Get the X axis speed. */
  int get_speedX();

  /** \brief Set the X axis speed. */
  void set_speedX( int speed );

  /** \brief Get current health. */
  int get_health();

  /** \brief Returns true if the Player has 0 lives left. */
  bool is_dead();

  /** \brief Set the health. */
  void set_health( int health );

 private:
  /** \brief The X axis speed modifier. */
  int speedX;

  /** \brief The current health. */
  int health;

};

#endif
