#include "playstate.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

PlayState::PlayState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures )
  :renderer{ renderer }, current_level{ 1 }, won_game{ false }, lost_game{ false }, score{ 0 }
{
  filter_textures( all_textures );
  load_important_objects();
  init();
}

PlayState::~PlayState()
{
  for ( Sprite* sprite : sprites )
  {
    delete sprite;
  }
}

void PlayState::filter_textures( map<string, SDL_Texture*>& all_textures )
{
  textures[ "player" ] = all_textures[ "player" ];
  textures[ "ball" ] = all_textures[ "ball" ];

  textures[ "green" ] = all_textures[ "green" ];
  textures[ "yellow" ] = all_textures[ "yellow" ];
  textures[ "red" ] = all_textures[ "red" ];

  textures[ "heart_1" ] = all_textures[ "heart_1" ];
  textures[ "heart_2" ] = all_textures[ "heart_2" ];
  textures[ "heart_3" ] = all_textures[ "heart_3" ];
  textures[ "heart_4" ] = all_textures[ "heart_4" ];
  textures[ "heart_5" ] = all_textures[ "heart_5" ];

  textures[ "none" ] = all_textures[ "none" ];

  textures[ "powerup" ] = all_textures[ "powerup" ];
}

/**
 * Loads objects, updates their sprites, sets speeds, adds bricks to the
 * `bricks` vector, and powerups to the `sprites` vector.
 */
void PlayState::init()
{
  load_objects();
  load_sprites();

  ball->set_speed( 13 );
  player->set_speedX( 8 );

  for ( Sprite* obj : sprites )
  {
    // extracts bricks
    if ( dynamic_cast<Brick*>(obj) )
    {
      Brick* brick = dynamic_cast<Brick*>(obj);
      bricks.push_back( brick );

      // if brick have powerup, add it to sprites.
      if ( brick->have_powerup() )
      {
	Powerup* powerup = brick->get_powerup();
	sprites.push_back( powerup );
      }
    }
  }
}

int PlayState::get_score()
{
  return score;
}

bool PlayState::have_won_the_game()
{
  return won_game;
}

bool PlayState::have_lost_the_game()
{
  return lost_game;
}

void PlayState::run( int& choosen )
{
  // handle events
  SDL_Event event;

  while ( SDL_PollEvent(&event) )
  {
    if ( event.type == SDL_QUIT )
    {
      choosen = 0;
      return;
    }
    if ( event.type == SDL_KEYDOWN )
    {
      switch( event.key.keysym.sym )
      {
      case SDLK_ESCAPE:
	choosen = 2;
      }
    }
  }

  // player
  const Uint8* key = SDL_GetKeyboardState( NULL );
  player->move( key );

  // ball
  ball->move();
  ball->bounce_walls();
  ball->hit_ground( player, choosen );
  ball->collide_player( player );

  // bricks
  int total_bricks = bricks.size();

  for ( Brick* brick : bricks )
  {
    brick->collide_ball( ball );

    if ( brick->is_dead() && brick->have_powerup() )
    {
      // powerup
      Powerup* powerup = brick->get_powerup();

      if ( powerup->is_active() )
      {
	powerup->update( player, ball );
      }
      else
      {
	brick->set_nullptr_powerup();
      }
    }

    if ( brick->is_dead() )
    {
      total_bricks -= 1;
    }
  }

  // heart
  heart->update_type( player );

  // if player is dead, lost the game
  if ( player->is_dead() )
  {
    lost_game = true;
  }
  // GAME STATUS
  // score
  score++;

  // next level
  if ( total_bricks <= 0 && won_game == false )
  {
    // player cleared level, go to next level
    level( current_level + 1 );
    choosen = 4;
    return;
  }

  // if gamestatus is win or loose, go to scoremenu
  if ( won_game || lost_game )
  {
    choosen = 3;
    return;
  }

  // clear screen
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // Draw sprites
  for ( Sprite* sprite : sprites )
  {
    sprite->update_sprite( textures );
    sprite->draw( renderer );
  }

  // show renderer
  SDL_RenderPresent( renderer );
}

void PlayState::level( int level )
{
  delete_bricks();
  current_level = level;
  init();
}

/**
 * Loads the ball, the player, and the heart sprite into the `sprites` vector.
 * It also sets the ball, player, and the heart instance variables.
 */
void PlayState::load_important_objects()
{
  ball = new Ball{ SCREEN_WIDTH / 2 - 32, SCREEN_HEIGHT - 200, 64, 64 };
  player = new Player{ ( SCREEN_WIDTH / 2 ) - ( 256 / 2 ), SCREEN_HEIGHT - 84, 300, 64 };
  heart = new Heart{ 30, 20, 200, 32 };

  sprites.push_back( ball );
  sprites.push_back( player );
  sprites.push_back( heart );
}

void PlayState::load_objects()
{
  switch ( current_level )
  {
  case 1:
    sprites.push_back( new Brick{ 100, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 300, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 500, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 700, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 900, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 1100, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 1300, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 1500, 152, 128, 64, 1 } );
    sprites.push_back( new Brick{ 1700, 152, 128, 64, 1, true } );
    break;
  case 2:
    reset_ball_and_player_position();

    sprites.push_back( new Brick{ 100, 152, 128, 64, 3 } );
    sprites.push_back( new Brick{ 300, 152, 128, 64, 3 } );
    sprites.push_back( new Brick{ 500, 152, 128, 64, 2 } );
    sprites.push_back( new Brick{ 700, 152, 128, 64, 2 } );
    sprites.push_back( new Brick{ 900, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 1100, 152, 128, 64, 2 } );
    sprites.push_back( new Brick{ 1300, 152, 128, 64, 2 } );
    sprites.push_back( new Brick{ 1500, 152, 128, 64, 3 } );
    sprites.push_back( new Brick{ 1700, 152, 128, 64, 3 } );
    break;
  case 3:
    reset_ball_and_player_position();

    sprites.push_back( new Brick{ 100, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 300, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 500, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 700, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 900, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 1100, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 1300, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 1500, 152, 128, 64, 1, true } );
    sprites.push_back( new Brick{ 1700, 152, 128, 64, 1, true } );
  default:
    won_game = true;
    break;
  }

}

void PlayState::reset_ball_and_player_position()
{
  player->set_X( ( SCREEN_WIDTH / 2 ) - ( 256 / 2 ) );
  ball->set_X( SCREEN_WIDTH / 2 - ( ball->get_W() / 2 ) );
  ball->set_Y( SCREEN_HEIGHT - 200 );
  ball->set_modifierY( 1 );
  ball->set_modifierX( 0 );
}

void PlayState::delete_bricks()
{
  vector<Sprite*>::iterator start_of_remove_bricks =
    remove_if(
	      sprites.begin(),
	      sprites.end(),
	      []( Sprite* current )->bool{
		if ( dynamic_cast<Brick*>(current) )
		{
		  delete current;
		  return true;
		}
		else if ( dynamic_cast<Powerup*>(current) )
		{
		  delete current;
		  return true;
		}
		return false;
	      }
	     );
  sprites.erase( start_of_remove_bricks, sprites.end() );
  bricks.erase( bricks.begin(), bricks.end() );
}

void PlayState::load_sprites()
{
  for ( Sprite* obj : sprites )
  {
    obj->update_sprite( textures );
  }
}
