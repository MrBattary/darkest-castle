//
// Created by Battary on 26.03.2020.
//

#include "game/systems/DebugSystem.h"

DebugSystem::DebugSystem() {
  setID(1099);
  addProcessedComponents(200, 201, 300);
}

void DebugSystem::updateSystem(ecs::World &world) {
  auto entities = world.getListEntities(getID());
  for (auto ent : entities) {
    auto locationComp = ent->getComponent<LocationComponent>();
    auto locationPreviousComp = ent->getComponent<PreviousLocationComponent>();
    auto controlComp = ent->getComponent<ControlComponent>();
    auto inputSystem = world.getSystem<InterfaceUpdateSystem>();

    std::string position = "[color=yellow]x: " + std::to_string(locationComp->column_) +
                           " xP: " + std::to_string(locationPreviousComp->columnPrevious_) +
                           "\ny: " + std::to_string(locationComp->row_) +
                           " yP: " + std::to_string(locationPreviousComp->rowPrevious_);
    std::string current = "[color=yellow]Now: " + controlComp->current_;
    std::string debug = "[color=green]DEBUG";

    int mainLayer = terminal_state(TK_LAYER);

    terminal_layer(mainLayer + 10);
    terminal_printf(34, 0, position.c_str());
    terminal_printf(34, 24, current.c_str());
    terminal_printf(0, 0, debug.c_str());
    terminal_printf(75, 0, debug.c_str());
    terminal_printf(0, 24, debug.c_str());
    terminal_printf(75, 24, debug.c_str());
    terminal_layer(mainLayer);
    // 79x24
  }
}
