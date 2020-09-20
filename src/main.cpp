#include "game/GameLoop.h"

int main() {
  terminal_open();

  std::unique_ptr<ecs::World> world = GameInit();
  GameLoop(std::move(world));

  terminal_close();

  return 0;
}
