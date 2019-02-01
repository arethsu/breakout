#include "sprite.h"

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


// Create a empty area object.
Sprite::Sprite()
  :texture{nullptr}
{
  ;
}

// Init rect with (x, y) when creating an area.
Sprite::Sprite( int x, int y )
  :texture{nullptr}, rect{ new SDL_Rect{ x, y, 0, 0 } }
{
  ;
}

// Init rect with (x, y, w, h) when creating an area.
Sprite::Sprite( int x, int y, int w, int h )
  :texture{nullptr}, rect{ new SDL_Rect{ x, y, w, h } }
{
  ;
}

Sprite::~Sprite()
{
  ;
}

void Sprite::update_sprite( map<string, SDL_Texture*>& textures )
{  
  try
  {
    set_texture( textures.at( get_type() ) );
  }
  catch (...)
  {
    set_texture( nullptr );
  }
}

void Sprite::draw( SDL_Renderer* renderer )
{
  SDL_RenderCopy( renderer, texture, NULL, get_rect() );
}

/** \brief Checks if the point is within the limits of this Sprite. */
bool Sprite::contain(int point_x, int point_y)
{
  return ( point_x >= get_X() && point_x <= get_X() + get_W() &&
           point_y >= get_Y() && point_y <= get_Y() + get_H() );
}

/** \brief Checks whether any corner of the Sprite is inside of this Sprite. */
bool Sprite::intersect(Sprite* a)
{
  // is there any corners from this area inside area "a"?
  if (
      contain( a->get_X(), a->get_Y() ) || contain( a->get_X()+a->get_W(), a->get_Y() ) ||
      contain( a->get_X(), a->get_Y()+a->get_H() ) || contain( a->get_X()+a->get_W(), a->get_Y()+a->get_H() )
     )
    return true;

  // is there any corners from area "a" inside this area?
  else if (
	   a->contain( get_X(), get_Y() ) || a->contain( get_X()+get_W(), get_Y() ) ||
	   a->contain( get_X(), get_Y()+get_H() ) || a->contain( get_X()+get_W(), get_Y()+get_H() )
	  )
    return true;

  // if no corners are inside any of the areas, there is no intersection
  return false;
}

// GETTERS

// get rect
SDL_Rect* Sprite::get_rect()
{
  return rect;
}

// get x-coordinate
int Sprite::get_X()
{
  return rect->x;
}

// get y-coordinate
int Sprite::get_Y()
{
  return rect->y;
}

// get width
int Sprite::get_W()
{
  return rect->w;
}

// get height
int Sprite::get_H()
{
  return rect->h;
}

// get horizontal center
double Sprite::get_centerX()
{
  return get_X()+(get_W()/2.0);
}

// get vertical center
double Sprite::get_centerY()
{
  return get_Y()+(get_H()/2.0);
}


// SETTERS

void Sprite::set_texture( SDL_Texture* t )
{
  texture = t;
}

// set x-coordinate
void Sprite::set_X(int x)
{
  rect->x = x;
}

// set y-coordinate
void Sprite::set_Y(int y)
{
  rect->y = y;
}

// set width
void Sprite::set_W(int w)
{
  rect->w = w;
}

// set height
void Sprite::set_H(int h)
{

  rect->h = h;
}
