#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <map>

using namespace std;

/** \brief Represents something to be draw on the screen. */
class Sprite
{
 public:
  Sprite();

  Sprite(int x, int y);
  Sprite(int x, int y, int w, int h);

  virtual ~Sprite();

  /** \brief Draws the Sprite onto the screen. */
  void draw( SDL_Renderer* renderer );

  /** \brief Update the texture according to the current type. */
  void update_sprite( map<string, SDL_Texture*>& textures );

  /** \brief Get the Sprite type */
  virtual string get_type() = 0;

   /** \brief Get the Sprite X coordinate. */
  int get_X();

  /** \brief Get the Sprite Y coordinate. */
  int get_Y();

  /** \brief Get the Sprite width. */
  int get_W();

  /** \brief Get the Sprite height. */
  int get_H();

  /** \brief Get center X coordinate. */
  double get_centerX();

  /** \brief Get center X coordinate. */
  double get_centerY();

  /** \brief Get the Sprite's SDL_Rect. */
  SDL_Rect* get_rect();

  /** \brief Set the Sprite X coordinate. */
  void set_X(int x);

  /** \brief Set the Sprite Y coordinate. */
  void set_Y(int y);

  /** \brief Set the Sprite width. */
  void set_W(int w);

  /** \brief Set the Sprite height. */
  void set_H(int h);

  /** \brief Sets the texture. */
  void set_texture( SDL_Texture* texture );

 private:
  /** The texture of this Sprite. */
  SDL_Texture* texture;

 protected:
  /** \brief The SDL_Rect used when passed to different SDL functions. */
  SDL_Rect* rect;

  /** \brief Used to calculate if another Sprite is intersecting with this area. */
  bool intersect(Sprite* a);

  /** \brief Used to calculate if a point (X, Y) exists within this Sprite. */
  bool contain(int point_x, int point_y);
};

#endif
