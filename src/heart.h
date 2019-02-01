#ifndef HEART_H
#define HEART_H

#include <string>

#include "sprite.h"
#include "player.h"

using namespace std;

/** \brief Represents an object on the screen that displays Player's current life. */
class Heart : public Sprite
{
 public:
  Heart( int x, int y, int w, int h );

  /** \brief Get the Heart game type. */
  string get_type();

  /** \brief Set the Heart type. */
  void set_type(string t);

  /** \brief Update the object type depending on the players health. */
  void update_type( Player* player );

 private:
  /** \brief The Heart type. Ex. "heart_1", "heart_2", "heart_3", etc.. */
  string type;
};

#endif
