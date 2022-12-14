#include "renderer.h"
#include "object.h"
#include "obstacle.h"
#include "player.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

// Main render method
void Renderer::Render(Player player, Object ground,
                      std::vector<Obstacle> &obstacles) {
  SDL_Rect block;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Draw the ground
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(sdl_renderer, 0, ground.GetAbsHeight(), screen_width,
                     ground.GetAbsHeight());

  // Render Player
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  block.w = player.get_width();
  block.h = -player.get_height();
  block.x = player.get_x();
  block.y = player.GetAbsHeight();
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render Obstacles
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  for (Obstacle &obstacle : obstacles) {
    block.w = obstacle.get_width();
    block.h = obstacle.get_height();
    block.x = obstacle.get_x();
    block.y = obstacle.get_y();
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(long int score, int fps, long int highscore) {
  std::string title{"Score: " + std::to_string(score) +
                    "  |  FPS: " + std::to_string(fps) +
                    "  |  Alltime Highscore: " + std::to_string(highscore)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
