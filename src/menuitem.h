#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include "sprite.h"

using namespace std;

/** \brief Represents a MenuItem in the MenuState. */
class MenuItem : public Sprite
{

 public:
  MenuItem();
  MenuItem( int x, int y, string type );
  MenuItem( int x, int y, int w, int h, string type );

  /** \brief Returns the object type. */
  string get_type();

  /** \brief Returns the raw type. Ex. "menu_start". */
  string get_true_type();

  /** \brief Sets the type. */
  void set_type( string type );

  /** \brief Set the selected attribute. */
  void set_selected( bool x );

  /** \brief Get the selected attribute. */
  bool get_selected();

 private:
  /** \brief The selected attribute. */
  bool selected{};

  string type{};

};

#endif
