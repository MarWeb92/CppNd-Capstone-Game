#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "obstacle.h"
#include "player.h"
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Player player, Object ground, std::vector<Obstacle> &obstacles);
  void UpdateWindowTitle(long int score, int fps, long int highscore);

private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif