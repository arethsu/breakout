#include "game.h"

using namespace std;

extern const int SCREEN_WIDTH = 1920;
extern const int SCREEN_HEIGHT = 1080;

Game::Game()
  :window{nullptr}, renderer{nullptr}
{
  if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
  {
    cerr << "Error initializing SDL" << endl;
    exit( 1 );
  }

  // initialize the window
  window =
    SDL_CreateWindow(
    "SDL Test",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    SDL_WINDOW_RESIZABLE
  );

  // initialize the renderer
  renderer = SDL_CreateRenderer( window, -1, 0 );

  sdl_settings();
}


void Game::load_textures()
{
  textures[ "player" ] = load_texture( "media/player.png" );

  textures[ "ball" ] = load_texture( "media/blue.png" );

  textures[ "green" ] = load_texture( "media/brick_green.png" );
  textures[ "yellow" ] = load_texture( "media/brick_yellow.png" );
  textures[ "red" ] = load_texture( "media/brick_red.png" );
  textures[ "powerup" ] = load_texture( "media/powerup.png" );

  textures[ "menu_start" ] = load_texture( "media/menu_start.png" );
  textures[ "menu_highscore" ] = load_texture( "media/menu_highscore.png" );
  textures[ "menu_menu" ] = load_texture( "media/menu_menu.png" );

  textures[ "menu_start_selected" ] = load_texture( "media/menu_start_selected.png" );
  textures[ "menu_highscore_selected" ] = load_texture( "media/menu_highscore_selected.png" );
  textures[ "menu_menu_selected" ] = load_texture( "media/menu_menu_selected.png" );

  textures[ "heart_1" ] = load_texture( "media/health_1.png" );
  textures[ "heart_2" ] = load_texture( "media/health_2.png" );
  textures[ "heart_3" ] = load_texture( "media/health_3.png" );
  textures[ "heart_4" ] = load_texture( "media/health_4.png" );
  textures[ "heart_5" ] = load_texture( "media/health_5.png" );

  textures[ "num_0" ] = load_texture( "media/0.png" );
  textures[ "num_1" ] = load_texture( "media/1.png" );
  textures[ "num_2" ] = load_texture( "media/2.png" );
  textures[ "num_3" ] = load_texture( "media/3.png" );
  textures[ "num_4" ] = load_texture( "media/4.png" );
  textures[ "num_5" ] = load_texture( "media/5.png" );
  textures[ "num_6" ] = load_texture( "media/6.png" );
  textures[ "num_7" ] = load_texture( "media/7.png" );
  textures[ "num_8" ] = load_texture( "media/8.png" );
  textures[ "num_9" ] = load_texture( "media/9.png" );

  textures[ "score_score" ] = load_texture( "media/score.png" );
  textures[ "score_winner" ] = load_texture( "media/winner.png" );
  textures[ "score_loser" ] = load_texture( "media/loser.png" );

  textures[ "none" ] = nullptr;
}

void Game::sdl_settings()
{
  // make the scaled rendering look smoother
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "linear" );

  // render at a virtual resolution then stretch to actual resolution
  SDL_RenderSetLogicalSize( renderer, SCREEN_WIDTH, SCREEN_HEIGHT );
}

/**
 * The main game loop. Handles a bunch of stuff, like:
 *
 * * Creates 3 game states, the PlayState, the MenuState, and the ScoreState.
 * * Creates a `choosen` variable that acts as the main switch between game states. A value of 0 quits the game.
 * * Runs all our states by using a switch statement inside of a while loop.
 * * Waits.
 * * Frees memory.
 */
void Game::run()
{
  load_textures();

  PlayState* playstate = new PlayState{ renderer, textures };
  MenuState* menustate = new MenuState{ renderer, textures };
  ScoreState* scorestate = new ScoreState{ renderer, textures };

  const Uint32 ticks_per_frame = 1000 / 60;

  int choosen{ 2 };
  const int play{ 1 };
  const int menu{ 2 };
  const int score{ 3 };
  const int pause_3_sec_then_play{ 4 };

  // main loop
  while ( choosen != 0 )
  {
    Uint32 ticks_start = SDL_GetTicks();

    switch ( choosen )
    {
    case play:
      scorestate->lost_the_game( false );
      scorestate->won_the_game( false );
      playstate->run( choosen );
      break;
    case menu:
      menustate->run( choosen );
      break;
    case score:
      if ( playstate->have_won_the_game() )
      {
	scorestate->update_score( playstate->get_score() );
	delete playstate;
        playstate = new PlayState{ renderer, textures };
	scorestate->won_the_game( true );
      }
      else if ( playstate->have_lost_the_game() )
      {
	scorestate->update_score( 999999999 );
	delete playstate;
        playstate = new PlayState{ renderer, textures };
	scorestate->lost_the_game( true );
      }

      scorestate->run( choosen );
      break;
    case pause_3_sec_then_play:
      SDL_Delay( 2000 );
      choosen = 1;
      break;
    default:
      choosen = 0;
      break;
    }

    // wait
    int wait = ticks_per_frame - ( SDL_GetTicks() - ticks_start );
    if ( wait > 0 )
    {
      SDL_Delay( wait );
    }
  }

  // free memory
  SDL_DestroyRenderer( renderer );
  SDL_DestroyWindow( window );
  delete playstate;
  delete menustate;
  delete scorestate;

  for ( pair<string,SDL_Texture*> texture : textures )
  {
    SDL_DestroyTexture( texture.second );
  }

  // quit sdl
  SDL_Quit();
}

// load texture function
SDL_Texture* Game::load_texture( const char* filename )
{
  SDL_Surface* temp_surface = IMG_Load( filename );
  SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, temp_surface );
  SDL_FreeSurface( temp_surface );

  return texture;
}
