//
// Created by Battary on 25.03.2020.
//

#include "game/GameLoop.h"

void GameLoop(std::unique_ptr<ecs::World> world) {
  do {
    terminal_clear();
    world->refreshWorld();
    terminal_refresh();
  } while (!world->getTerminateApplicationStatus());
}
