#include "ball.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Ball::Ball( int x, int y, int w, int h ):
Sprite{ x, y, w, h }, modifierX{ 0 }, modifierY{ 1 } {;}

/**
 * Sets new coordinates depending on the X and Y modifiers and speed.
 */
void Ball::move()
{
  set_X( get_X() + get_speed() * get_modifierX() );
  set_Y( get_Y() + get_speed() * get_modifierY() );
}

/**
 * Handles when a ball has hit the ground. When the ball is outside of the
 * ground, this function will perform a set of tasks to handle such a situation.
 * First it subtracts 1 from the Player's health, second it resets the Ball's
 * position and makes sure that it will fly straight down when unpaused, third
 * it will reset the Player's position and width to its default state, and last,
 * it will pause the game by setting `choosen` to 4, which represents a pause of
 * 3 seconds before resuming the game again.
 */
void Ball::hit_ground( Player* player, int& choosen )
{
  if ( get_Y() + get_H() > SCREEN_HEIGHT )
  {

    player->set_health( player->get_health() - 1 );

    // reset ball position
    set_X( SCREEN_WIDTH / 2 - ( get_W() / 2 ) );
    set_Y( SCREEN_HEIGHT - 200 );
    set_modifierY( 1 );
    set_modifierX( 0 );

    // reset player position and status
    player->set_W( 300 );
    player->set_X( SCREEN_WIDTH / 2 - ( player->get_W() / 2 ) );

    choosen = 4; // pause
  }
}

void Ball::bounce_walls()
{
  if ( get_X() + get_W() > SCREEN_WIDTH || get_X() < 0 )
  {
    set_modifierX( 0 - get_modifierX() );
  }

  if ( get_Y() < 0 )
  {
    set_modifierY( 0 - get_modifierY() );
  }
}

/**
 * Modifies the Ball's `X` and `Y` modifiers. These are then used within
 * `move()` to update the Ball's position.
 *
 * The function is built in a manner that lets the Player control in which way
 * the Ball is going to bounce.
 *
 * When a ball lands on the Player, it will figure out where it landed. Landing
 * horizontally in the middle of the Player would cause the ball to fly straight
 * up. Landing on the left side of the Player would cause the ball to bounce to
 * the left. Landing on the right side of the Player would cause the ball to
 * bounce to the right. The further out on the player it lands, the steeper the
 * angle.
 */
void Ball::collide_player(Player* player)
{
  if ( intersect(player) )
  {
    // 0 -> 1
    double percentage_overall ( ( get_centerX() - player->get_X() ) / player->get_W() );
    if ( percentage_overall < 0.5 )
    {
      // 0 = 100%, 0.5 = 0%
      double percentage_middle_to_left{ (0.5 - percentage_overall) / 0.5 };
      set_modifierX( 0 - ( ( percentage_middle_to_left - 0.2 ) * 2 ) );
      set_modifierY( 0 - ( 1 - percentage_middle_to_left ) );
    }
    else
    {
      // 1 = 100%, 0.5 = 0%
      double percentage_middle_to_right{ 0 };

      if ( percentage_overall - 0.5 != 0 )
      {
        percentage_middle_to_right = ( percentage_overall - 0.5 ) / 0.5;
      }
      set_modifierX( ( percentage_middle_to_right - 0.2 ) * 2 );
      set_modifierY( 0 - ( 1 - percentage_middle_to_right ) );
    }
  }
}

// SETTERS
void Ball::set_speed(int s)
{
  speed = s;
}

void Ball::set_modifierX(double modX)
{
  modifierX = modX;
}

void Ball::set_modifierY(double modY)
{
  modifierY = modY;
}

// GETTERS
int Ball::get_speed()
{
  return speed;
}

double Ball::get_modifierX()
{
  return modifierX;
}

double Ball::get_modifierY()
{
  return modifierY;
}

string Ball::get_type()
{
  return "ball";
}
