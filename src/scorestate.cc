#include "scorestate.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

ScoreState::ScoreState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures )
  :renderer{ renderer }, won_game{ false }, lost_game{ false }, score { 0 }
{
  filter_textures( all_textures );
  init();
}


ScoreState::~ScoreState()
{
  for ( Sprite* sprite : sprites )
  {
    delete sprite;
  }
}

void ScoreState::filter_textures( map<string, SDL_Texture*>& all_textures )
{
  textures[ "menu_menu" ] = all_textures[ "menu_menu" ];
  textures[ "menu_menu_selected" ] = all_textures[ "menu_menu_selected" ];

  textures[ "score_score" ] = all_textures[ "score_score" ];
  textures[ "score_winner" ] = all_textures[ "score_winner" ];
  textures[ "score_loser" ] = all_textures[ "score_loser" ];

  textures[ "num_0" ] = all_textures[ "num_0" ];
  textures[ "num_1" ] = all_textures[ "num_1" ];
  textures[ "num_2" ] = all_textures[ "num_2" ];
  textures[ "num_3" ] = all_textures[ "num_3" ];
  textures[ "num_4" ] = all_textures[ "num_4" ];
  textures[ "num_5" ] = all_textures[ "num_5" ];
  textures[ "num_6" ] = all_textures[ "num_6" ];
  textures[ "num_7" ] = all_textures[ "num_7" ];
  textures[ "num_8" ] = all_textures[ "num_8" ];
  textures[ "num_9" ] = all_textures[ "num_9" ];

  textures[ "none" ] = all_textures[ "none" ];
}

void ScoreState::init()
{
  load_objects();
  load_sprites();

  for ( Sprite* obj : sprites )
  {
    // extract menu_items
    if ( dynamic_cast<MenuItem*>(obj) )
    {
      menu_items.push_back( dynamic_cast<MenuItem*>(obj) );
    }
  }
}

void ScoreState::load_score_text()
{
  string score_string = to_string(score);
  stringstream score_stream( score_string );
  int x_pos{ SCREEN_WIDTH / 2 - 100 };
  string letter;

  for ( char c : score_string )
  {
    x_pos += 32;
    sprites.push_back( new Background{ x_pos, 317, 32, 32, "num_"+string(1,c) } );
  }
}

void ScoreState::hide_score_text()
{
  for ( Sprite* obj : sprites )
  {
    if ( dynamic_cast<Background*>(obj) )
    {
      Background* background = dynamic_cast<Background*>(obj);

      if ( regex_match( background->get_type(), regex( "(num_)(.*)" ) ) )
      {
        background->set_type( "none" );
      }
    }
  }
}

void ScoreState::won_the_game( bool won )
{
  won_game = won;
}

void ScoreState::lost_the_game( bool lost )
{
  lost_game = lost;
}

void ScoreState::move_down()
{
  bool found_something{ false };

  for ( unsigned int i{ 0 }; i < menu_items.size(); i++ )
  {
    if ( menu_items.at( i )->get_selected() == true )
    {
      found_something = true;
      if ( i < ( menu_items.size() - 1 ) )
      {
	menu_items.at( i )->set_selected( false );
	menu_items.at( i+1 )->set_selected( true );
	break;
      }
    }
  }

  if ( ! found_something )
  {
    menu_items.at(0)->set_selected( true );
  }
}

void ScoreState::move_up()
{
  bool found_something{ false };

  for ( unsigned int i{ 0 }; i < menu_items.size(); i++ )
  {
    if ( menu_items.at( i )->get_selected() == true )
    {
      found_something = true;
      if ( i != 0 )
      {
	menu_items.at( i )->set_selected( false );
	menu_items.at( i-1 )->set_selected( true );
	break;
      }
    }
  }

  if ( ! found_something )
  {
    menu_items.at(0)->set_selected( true );
  }
}

void ScoreState::select_current_menu_item( int& choosen )
{
  for ( MenuItem* menuitem : menu_items )
  {
    if ( menuitem->get_selected() == true )
    {
      if ( menuitem->get_true_type() ==  "menu_menu" )
      {
        choosen = 2;
      }
    }
  }
}

/**
 * ScoreState handles itself like this:
 *
 * * Checks if we need to quit the game, if so, it sets `choosen` to 0 which in turn quits the game.
 * * Checks whether we pressed "W", "S", or "RETURN", and uses `move_up()`, `move_down()`, and `select_current_menu_item()` accordingly.
 * * Clears the screen, updates, and draws all sprites.
 */
void ScoreState::run( int& choosen )
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
    switch ( event.type )
    {
    case SDL_KEYDOWN:
      switch ( event.key.keysym.sym )
      {
      // move up
      case SDLK_w:
	move_up();
	break;
      // move down
      case SDLK_s:
        move_down();
	break;
      // choose
      case SDLK_RETURN:
	select_current_menu_item( choosen );
	break;
      }
    }
  }

  // clear screen
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // Draw sprites
  for ( Sprite* sprite : sprites )
  {
    if ( sprite->get_type() == "score_winner" )
    {
      if ( won_game )
      {
	sprite->update_sprite( textures );
	sprite->draw( renderer );
      }
    }
    else if ( sprite->get_type() == "score_loser" )
    {
      if ( lost_game )
      {
	sprite->update_sprite( textures );
	sprite->draw( renderer );
      }
    }
    else
    {
      sprite->update_sprite( textures );
      sprite->draw( renderer );
    }
  }

  // show renderer
  SDL_RenderPresent( renderer );
}

void ScoreState::load_objects()
{
  // in order
  sprites.push_back( new MenuItem{ SCREEN_WIDTH / 2 - 300, 800, 600, 100, "menu_menu" } );
  sprites.push_back( new Background{ SCREEN_WIDTH / 2 - 300, 300, 200, 64, "score_score" } );
  sprites.push_back( new Background{ SCREEN_WIDTH / 2 - 300, 100, 600, 100, "score_loser" } );
  sprites.push_back( new Background{ SCREEN_WIDTH / 2 - 300, 100, 600, 100, "score_winner" } );
}

void ScoreState::load_sprites()
{
  for ( Sprite* obj : sprites )
  {
    obj->update_sprite( textures );
  }
}

int ScoreState::get_score()
{
  return score;
}

void ScoreState::update_score( int s )
{
  score = s;
  hide_score_text();
  load_score_text();
}
