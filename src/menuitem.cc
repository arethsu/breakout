#include "menuitem.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

MenuItem::MenuItem( int x, int y, string type )
  :Sprite{ x, y }, selected{ false }, type{ type }
{
  ;
}

MenuItem::MenuItem( int x, int y, int w, int h, string type )
  :Sprite( x, y, w, h ), selected{ false }, type{ type }
{
  ;
}

void MenuItem::set_type( string t )
{
  type = t;
}

/**
 * Returns the object type. Ex. "menu_start_selected" if the MenuItem is
 * currently selected. This way we'll be able to set the correct texture.
 */
string MenuItem::get_type()
{
  if ( get_selected() )
  {
    return type + "_selected";
  }
  else
  {
    return type;
  }
}

string MenuItem::get_true_type()
{
  return type;
}

bool MenuItem::get_selected()
{
  return selected;
}

void MenuItem::set_selected(bool x)
{
  selected = x;
}
