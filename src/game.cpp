#include "game.h"
#include "SDL.h"
#include "obstacle.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>

// Constructor
Game::Game(int screenWidth, int screenHeight, const int groundLvl,
           const int startPlayer_x, const int startPlayer_y,
           const int playerWidth, const int playerHeight)
    : player(startPlayer_x, startPlayer_y, playerWidth, playerHeight, groundLvl,
             screenWidth, screenHeight),
      ground(0, groundLvl, 0, 0, screenHeight), engine(dev()) {

  // Run the member method in a parallel thread to trigger obstacle gen.
  threads.emplace_back(std::move(std::thread(&Game::getObstacleTrigger, this)));

  // read in highscore if available
  std::string line;
  std::ifstream inputFileStream("gamedata.txt");
  if (inputFileStream.is_open()) {
    std::getline(inputFileStream, line);
    std::istringstream linestream(line);
    linestream >> _highscore;
    inputFileStream.close();
  }
}

// Destructor
Game::~Game() {
  // thread barrier for all started threads before Game is destructed
  std::for_each(threads.begin(), threads.end(),
                [](std::thread &t) { t.join(); });

  // save all time highscore
  std::ofstream dataFile;
  dataFile.open("gamedata.txt");
  dataFile << _highscore;
  dataFile.close();
}

// Endless loop implementing the game loop
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
      renderer.UpdateWindowTitle(score, frame_count, _highscore);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

// Update method will call the Update methods of all relevant objects
// Furthermore this will create the obstacles
void Game::Update() {

  int random_y; // on which level to put the obstacles
  int random_w; // random width of obstacle
  int random_h; // random height of obstacle
  std::uniform_int_distribution<int> rand_dist_height(0, ground.GetAbsHeight());
  std::uniform_int_distribution<int> rand_dist_length_width(5, 200);

  // do not update anything no more, if player is dead
  if (!player.alive)
    return;

  // detect if collision occured
  if (CheckCollision())
    player.alive = false;

  // create new obstacle
  if (triggerNewObstacle == true) {
    random_y = rand_dist_height(engine);
    random_w = rand_dist_length_width(engine);
    random_h = rand_dist_length_width(engine);

    Obstacle obstcl(1300, random_y, random_w, random_h, 1280, 640, 3);
    obstacles.push_back(obstcl);
    triggerNewObstacle = false;
  }

  // update player and obstacles
  player.Update();

  for (Obstacle &obstacle : obstacles) {
    obstacle.Update();
  }

  // clean up vector of obstacles that already vanished
  for (std::vector<Obstacle>::iterator it = obstacles.begin();
       it != obstacles.end(); it++) {
    if (it->get_x() <= -250) {
      obstacles.erase(it);
    }
  }

  // score equals the number of created obstacles
  score = Obstacle::get_blockCtr();

  // update highscore if score is higher
  score > _highscore ? _highscore = score : _highscore = _highscore;
}

int Game::GetScore() const { return score; }

// This function implements an endless loop, run in a seperate thread
// It cyclically gives a trigger to create a new obstacle
void Game::getObstacleTrigger() {

  // create random duration time between 500ms and 3s
  std::uniform_int_distribution<int> dist(500, 3000);
  int cycleDuration = dist(engine);

  // get initial time point
  auto time1 = std::chrono::system_clock::now();

  while (player.alive) {
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

// This function checks if the player has collided with one of the obstacles.
// Basic concept is to look at the x and y coordinates and the width and height
// of the objects. If the x coordinate range of the player overlaps with the x
// coordinate range of one of the obstacles AND the y coordinate range of the
// player overlaps with the y coordinate range of THAT SAME obstacle, then a
// collision occured!
bool Game::CheckCollision() {
  bool returnVal{false};
  bool xOverlap{false};
  bool yOverlap{false};

  for (auto obstacle : obstacles) {
    // check for x-Coordinate overlapping with all obstacles
    if ((player.get_x() >= obstacle.get_x()) &&
            (player.get_x() <= (obstacle.get_x() + obstacle.get_width())) ||
        ((player.get_x() + player.get_width() >= obstacle.get_x()) &&
         (player.get_x() + player.get_width()) <=
             (obstacle.get_x() + obstacle.get_width()))) {
      xOverlap |= true;
    } else {
      xOverlap |= false;
    }

    // check for y-Coordinate overlapping with all obstacles
    if ((player.GetAbsHeight() >= obstacle.get_y()) &&
            (player.GetAbsHeight() <=
             (obstacle.get_y() + obstacle.get_height())) ||
        ((player.GetAbsHeight() - player.get_height() >= obstacle.get_y()) &&
         (player.GetAbsHeight() - player.get_height()) <=
             (obstacle.get_y() + obstacle.get_height()))) {
      yOverlap |= true;
    } else {
      yOverlap |= false;
    }

    // if both overlapps occure for one obstacle --> COLLISION
    if (xOverlap && yOverlap) {
      returnVal = true;
    }
    xOverlap = false;
    yOverlap = false;
  }

  return returnVal;
}