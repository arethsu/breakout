#include "brick.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Brick::Brick( int x, int y, int w, int h, int health, bool have_powerup )
  :Sprite( x, y, w, h ), health{ health }, powerup{ nullptr }
{
  if ( have_powerup )
  {
    powerup = new Powerup{ x, y, 64, 64 };
  }

  update_type();
}

Brick::~Brick()
{
  ;
}

string Brick::get_type()
{
  return type;
}

bool Brick::is_dead()
{
  return ( get_health() <= 0 );
}

/**
 * Updates the Brick game type so that the texture may be changed.
 */
void Brick::update_type()
{
  switch ( get_health() )
  {
    case 0:
      set_type("none");
      break;
    case 1:
      set_type("green");
      break;
    case 2:
      set_type("yellow");
      break;
    case 3:
      set_type("red");
      break;
  }
}

void Brick::set_type(string t)
{
  type = t;
}

void Brick::set_nullptr_powerup()
{
  powerup = nullptr;
}

/**
 * Returns true if the private instance variable `powerup` isn't a `nullptr`.
 */
bool Brick::have_powerup()
{
  return ( powerup != nullptr );
}

Powerup* Brick::get_powerup()
{
  return powerup;
}

/**
 * Repells the ball by making its modifiers negative. Also subtracts 1 from the
 * Brick's health and updates the Brick type (gets a new texture).
 */
void Brick::collide_ball(Ball* ball)
{
  if ( intersect( ball ) && is_dead() == false )
  {
    ball->set_modifierX( 0 - ball->get_modifierX() );
    ball->set_modifierY( 0 - ball->get_modifierY() );
    
    set_health(get_health()-1); 
    
    update_type();
  }
}

int Brick::get_health()
{
  return health;
}

void Brick::set_health(int h)
{
  if ( h >= 0 )
  {
    health = h;
  }
}
