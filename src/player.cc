#include "player.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Player::Player(int x, int y, int w, int h)
  :Sprite{x,y,w,h}, health{5}
{
  ;
}

/**
 * Moves the Player only if the A or D key is pressed down and it's not outside
 * the game screen.
 */
void Player::move(const Uint8* key)
{
  if ( ( get_X() + get_W() <= SCREEN_WIDTH ) && key[ SDL_SCANCODE_D ] )
  {
    set_X( get_X() + get_speedX() );
  }

  if ( ( get_X() >= 0 ) && key[ SDL_SCANCODE_A ] )
  {
    set_X( get_X() - get_speedX() );
  }
}

bool Player::is_dead()
{
  return ( get_health() <= 0 );
}

string Player::get_type()
{
  return "player";
}

int Player::get_speedX()
{
  return speedX;
}

void Player::set_speedX(int x)
{
  speedX = x;
}

void Player::set_health( int h )
{
  health = h;
}

int Player::get_health()
{
  return health;
}
