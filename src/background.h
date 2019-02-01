#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <string>

#include "sprite.h"

using namespace std;

/** \brief Represents a background. */
class Background : public Sprite
{
 public:
  Background( int x, int y, int w, int h, string type );

  /** \brief Get the Background type. */
  string get_type();

  /** \brief Set the Background type. */  
  void set_type( string type );

 private:
  string type;
};

#endif
