#include "menustate.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

MenuState::MenuState( SDL_Renderer* renderer, map<string, SDL_Texture*>& all_textures )
  :renderer{ renderer }
{
  filter_textures( all_textures );
  init();
}


MenuState::~MenuState()
{
  for ( Sprite* sprite : sprites )
  {
    delete sprite;
  }
}

void MenuState::filter_textures( map<string, SDL_Texture*>& all_textures )
{
  textures[ "menu_start" ] = all_textures[ "menu_start" ];
  textures[ "menu_highscore" ] = all_textures[ "menu_highscore" ];

  textures[ "menu_start_selected" ] = all_textures[ "menu_start_selected" ];
  textures[ "menu_highscore_selected" ] = all_textures[ "menu_highscore_selected" ];

  textures[ "none" ] = all_textures[ "none" ];
}

void MenuState::init()
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

void MenuState::move_down()
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

void MenuState::move_up()
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

void MenuState::select_current_menu_item( int& choosen )
{
  for ( MenuItem* menuitem : menu_items )
  {
    if ( menuitem->get_selected() == true )
    {
      if ( menuitem->get_true_type() ==  "menu_start" )
      {
        choosen = 1;
      }
      if ( menuitem->get_true_type() ==  "menu_highscore" )
      {
        choosen = 3;
      }
    }
  }
}

/**
 * MenuState is the selection screen that appears when the game starts. This is
 * how it handles itself:
 *
 * * Checks if we need to quit the game, if so, it sets `choosen` to 0 which in turn quits the game.
 * * Checks whether we pressed "W", "S", or "RETURN", and uses `move_up()`, `move_down()`, and `select_current_menu_item()` accordingly.
 * * Clears the screen, updates, and draws all sprites.
 */
void MenuState::run( int& choosen )
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
      case SDLK_RETURN:
	select_current_menu_item( choosen );
	break;
      }
    }
  }

  /*
  player->move( key );
  */

  // move menu-item with keys.

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

void MenuState::load_objects()
{
  // in order
  sprites.push_back( new MenuItem{ SCREEN_WIDTH / 2 - 300, 400, 600, 100, "menu_start" } );
  sprites.push_back( new MenuItem{ SCREEN_WIDTH / 2 - 300, 600, 600, 100, "menu_highscore" } );
}

void MenuState::load_sprites()
{
  for ( Sprite* obj : sprites )
  {
    obj->update_sprite( textures );
  }
}
