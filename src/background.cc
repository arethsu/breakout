#include "background.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Background::Background( int x, int y, int w, int h, string type )
  :Sprite( x, y, w, h ), type{ type }
{
  ;
}

string Background::get_type()
{
  return type;
}

void Background::set_type( string t)
{
  type = t;
}
