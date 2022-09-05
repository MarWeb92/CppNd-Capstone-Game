#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "object.h"
#include "obstacle.h"
#include "player.h"
#include "renderer.h"
#include <thread>
#include <random>

class Game {
public:
  Game(int screenWidth, int screenHeight, const int groundLvl,
       const int startPlayer_x, const int startPlayer_y);
  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void getObstacleTrigger();
  int GetScore() const;
  int GetSize() const;

private:
  Player player;
  Object ground;
  std::vector<Obstacle> obstacles{};
  bool triggerNewObstacle{true};
  std::vector<std::thread> threads;

  std::random_device dev;
  std::mt19937 engine;

  int score{0};

  void Update();
};

#endif