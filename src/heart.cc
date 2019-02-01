#include "heart.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Heart::Heart( int x, int y, int w, int h )
  :Sprite( x, y, w, h )
{
  ;
}

string Heart::get_type()
{
  return type;
}

void Heart::set_type(string t)
{
  type = t;
}

void Heart::update_type( Player* player )
{
  switch ( player->get_health() )
  {
  case 1:
    set_type("heart_1");
    break;
  case 2:
    set_type("heart_2");
    break;
  case 3:
    set_type("heart_3");
    break;
  case 4:
    set_type("heart_4");
    break;
  case 5:
    set_type("heart_5");
    break;
  default:
    set_type("none");
    break;
  }
}
