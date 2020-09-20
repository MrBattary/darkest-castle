//
// Created by Battary on 26.05.2020.
//

#include "game/systems/collisionSubsystems/ExitCollision.h"

void ExitCollision::updateData(ecs::World &world, std::shared_ptr<ecs::Entity> first,
                               std::shared_ptr<ecs::Entity> second) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  auto firstDataComp = first->getComponent<ExitDataComponent>();
  auto currentPosComp = second->getComponent<LocationComponent>();
  auto previousPosComp = second->getComponent<PreviousLocationComponent>();
  auto directionComp = second->getComponent<DirectionComponent>();

  if (directionComp->direction_ == DirectionComponent::UPWARD ||
      directionComp->direction_ == DirectionComponent::DOWNWARD) {
    currentPosComp->row_ = previousPosComp->rowPrevious_;
    previousPosComp->columnPrevious_ = currentPosComp->column_;
  }
  if (directionComp->direction_ == DirectionComponent::LEFTWARD ||
      directionComp->direction_ == DirectionComponent::RIGHTWARD) {
    currentPosComp->column_ = previousPosComp->columnPrevious_;
    previousPosComp->rowPrevious_ = currentPosComp->row_;
  }

  directionComp->direction_ = DirectionComponent::NOWHERE;

  // Очистка логики врагов
  auto entities = world.getListEntities(300);
  for (auto entity : entities) {
    auto prevLocComp = entity->getComponent<PreviousLocationComponent>();
    auto logicComp = entity->getComponent<EnemyLogicComponent>();
    logicComp->steps_.clear();
    logicComp->steps_.push_back(std::make_pair(prevLocComp->columnPrevious_, prevLocComp->rowPrevious_));
  }

  interfaceSys->createElement<EndLevelBox>(world, firstDataComp->toX_, firstDataComp->toY_, firstDataComp->map_);
  interfaceSys->createElement<LeaderboardBox>();
}

void ExitCollision::updateSubsystem(ecs::World &world, std::shared_ptr<ecs::Entity> first,
                                    std::shared_ptr<ecs::Entity> second) {
  std::string firstName = first->getEntityName();
  std::string secondName = second->getEntityName();

  if (firstName == "Exit") {
    updateData(world, first, second);
  } else {
    updateData(world, second, first);
  }
  world.updateWorldList();
}
