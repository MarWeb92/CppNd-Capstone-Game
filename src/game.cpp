#include "game.h"
#include "SDL.h"
#include "obstacle.h"
#include <iostream>

Game::Game(int screenWidth, int screenHeight, const int groundLvl,
           const int startPlayer_x, const int startPlayer_y)
    : player(startPlayer_x, startPlayer_y, groundLvl, screenWidth,
             screenHeight),
      ground(0, groundLvl, screenHeight), engine(dev()) {}

void Game::Run(Controller &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);
    Update();
    renderer.Render(player, ground, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    std::cout << "Player X: " << player.get_x() << "\n";
    std::cout << "Player y: " << player.get_y() << "\n";
  }
}

void Game::Update() {

  int random_y;
  int random_w;
  int random_h;
  std::uniform_int_distribution<int> rand_dist_height(0, ground.GetAbsHeight());
  std::uniform_int_distribution<int> rand_dist_length_width(5, 200);

  if (!player.alive)
    return;

  if (tryout == true) {
    random_y = rand_dist_height(engine);
    random_w = rand_dist_length_width(engine);
    random_h = rand_dist_length_width(engine);

    Obstacle one(2000, random_y, random_w, random_h, 1280, 640, 3);
    obstacles.push_back(one);
    tryout = false;
  }

  player.Update();

  for (Obstacle &obstacle : obstacles) {
    obstacle.Update();
  }

  int new_x = static_cast<int>(player.get_x());
  int new_y = static_cast<int>(player.get_y());
}

int Game::GetScore() const { return score; }