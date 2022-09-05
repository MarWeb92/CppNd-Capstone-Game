#include "game.h"
#include "SDL.h"
#include "obstacle.h"
#include <chrono>
#include <iostream>
#include <thread>

Game::Game(int screenWidth, int screenHeight, const int groundLvl,
           const int startPlayer_x, const int startPlayer_y, const int playerWidth, const int playerHeight)
    : player(startPlayer_x, startPlayer_y, playerWidth,playerHeight, groundLvl, screenWidth,
             screenHeight),
      ground(0, groundLvl, 0,0, screenHeight), engine(dev()) {
  threads.emplace_back(std::move(std::thread(&Game::getObstacleTrigger, this)));
}

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
    std::cout << "Number of array elements " << obstacles.size() << "\n";
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

  if (triggerNewObstacle == true) {
    random_y = rand_dist_height(engine);
    random_w = rand_dist_length_width(engine);
    random_h = rand_dist_length_width(engine);

    Obstacle one(2000, random_y, random_w, random_h, 1280, 640, 3);
    obstacles.push_back(one);
    triggerNewObstacle = false;
  }

  player.Update();

  for (Obstacle &obstacle : obstacles) {
    obstacle.Update();
  }

  // clean up vector
  for (std::vector<Obstacle>::iterator it = obstacles.begin();
       it != obstacles.end(); it++) {
    if (it->get_x() <= -500) {
      obstacles.erase(it);
    }
  }

  score = Obstacle::get_blockCtr();
}

int Game::GetScore() const { return score; }

// virtual function which is executed in a thread
void Game::getObstacleTrigger() {

  // create random duration time
  std::uniform_int_distribution<int> dist(500, 3000);
  int cycleDuration = dist(engine);

  // get initial time point
  auto time1 = std::chrono::system_clock::now();

  while (true) {
    auto time2 = std::chrono::system_clock::now();
    auto time_diff =
        std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1)
            .count();

    if (time_diff >= cycleDuration) {
      // trigger creation of another block
      triggerNewObstacle = true;

      // update time1
      time1 = std::chrono::system_clock::now();

      // get new random duration time
      cycleDuration = dist(engine);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

bool Game::CheckCollision() {
  bool returnVal{false};

  return returnVal;
}