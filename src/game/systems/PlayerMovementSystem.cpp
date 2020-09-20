//
// Created by Battary on 26.03.2020.
//

#include "game/systems/PlayerMovementSystem.h"

PlayerMovementSystem::PlayerMovementSystem() {
  setID(200);
  addProcessedComponents(200, 201, 202, 300, 400);
  fillStorage();
}

void PlayerMovementSystem::fillStorage() {
  storage_["Move right"] = std::make_shared<MoveRightCommand>();
  storage_["Move left"] = std::make_shared<MoveLeftCommand>();
  storage_["Move up"] = std::make_shared<MoveUpCommand>();
  storage_["Move down"] = std::make_shared<MoveDownCommand>();
}

std::shared_ptr<ICommand> PlayerMovementSystem::findCommand(const std::string command) {
  auto it = storage_.find(command);
  if (it == storage_.end()) {
    return nothing_;
  } else {
    return storage_.at(command);
  }
}

void PlayerMovementSystem::updateSystem(ecs::World &world) {
  auto entities = world.getListEntities(getID());
  for (auto ent : entities) {
    auto controlComp = ent->getComponent<ControlComponent>();
    auto locationComp = ent->getComponent<LocationComponent>();
    auto locationPreviousComp = ent->getComponent<PreviousLocationComponent>();
    auto statisticsComp = ent->getComponent<StatisticsComponent>();
    auto directionComp = ent->getComponent<DirectionComponent>();

    const std::string current {controlComp->current_};
    controlComp->current_.clear();

    auto command = findCommand(current);
    command->execute(locationComp, locationPreviousComp, directionComp, statisticsComp);
  }
}
