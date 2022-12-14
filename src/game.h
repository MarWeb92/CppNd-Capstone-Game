#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "object.h"
#include "obstacle.h"
#include "player.h"
#include "renderer.h"
#include <random>
#include <thread>

class Game {
public:
  Game(int screenWidth, int screenHeight, const int groundLvl,
       const int startPlayer_x, const int startPlayer_y, const int playerWidth,
       const int playerHeight);
  ~Game();

  void Run(Controller &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  int GetScore() const;

private:
  void getObstacleTrigger();
  bool CheckCollision();

  Player player;
  Object ground;
  std::vector<Obstacle> obstacles{};
  bool triggerNewObstacle{true};
  std::vector<std::thread> threads;

  std::random_device dev;
  std::mt19937 engine;

  long int score{0};
  long int _highscore{0};

  void Update();
};

#endif