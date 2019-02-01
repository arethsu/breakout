#include "powerup.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Powerup::Powerup( int x, int y, int w, int h )
  :Sprite{ x, y, w, h }, speed{ 2 }, active{ true }, type{ "powerup" }
{
  ;
}

bool Powerup::is_active()
{
  return active;
}

void Powerup::move()
{
  set_Y( get_Y() + get_speed() );
}

/**
 * * Moves the Powerup.
 * * Does a random effect if intersecting with Player.
 * * Checks if it has hit the ground yet.
 */
void Powerup::update( Player* player, Ball* ball )
{
  move();
  do_random_effect( player, ball );
  hit_ground();
}

void Powerup::do_random_effect( Player* player, Ball* ball )
{
  if ( intersect( player ) )
  {
    random_device gen;
    uniform_int_distribution<int> dist(1,3);
    int rand{ dist( gen ) };

    switch ( rand )
    {
    case 1:
      player->set_W( 100 );
      deactivate();
      break;
    case 2:
      player->set_W( 500 );
      deactivate();
      break;
    case 3:
      player->set_speedX( 12 );
      deactivate();
      break;
    }
  }
}

/**
 * Deactivates the Powerup by setting `active` to `false` and then setting the
 * `type` to `none` which will remove the Powerup's texture.
 */
void Powerup::deactivate()
{
  active = false;
  type = "none";
}

void Powerup::hit_ground()
{
  if ( get_Y() + get_H() > SCREEN_HEIGHT )
  {
    deactivate();
  }
}

// GETTERS
int Powerup::get_speed()
{
  return speed;
}

string Powerup::get_type()
{
  return type;
}
