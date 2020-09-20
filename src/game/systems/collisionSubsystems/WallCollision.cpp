//
// Created by Battary on 27.04.2020.
//

#include "game/systems/collisionSubsystems/WallCollision.h"

void WallCollision::updateData(ecs::World& world, std::shared_ptr<ecs::Entity> first,
                               std::shared_ptr<ecs::Entity> second) {
  auto positionComp = first->getComponent<LocationComponent>();
  auto positionPreviousComp = first->getComponent<PreviousLocationComponent>();
  auto directionComp = first->getComponent<DirectionComponent>();

  if (directionComp->direction_ == DirectionComponent::UPWARD ||
      directionComp->direction_ == DirectionComponent::DOWNWARD) {
    positionComp->row_ = positionPreviousComp->rowPrevious_;
  }
  if (directionComp->direction_ == DirectionComponent::LEFTWARD ||
      directionComp->direction_ == DirectionComponent::RIGHTWARD) {
    positionComp->column_ = positionPreviousComp->columnPrevious_;
  }
  directionComp->direction_ = DirectionComponent::NOWHERE;

  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  auto logBox = interfaceSys->getElement<PlayerRealtimeLogBox>();
  logBox->addData("There's no way through ");
}

void WallCollision::updateSubsystem(ecs::World& world, std::shared_ptr<ecs::Entity> first,
                                    std::shared_ptr<ecs::Entity> second) {
  std::string firstName = first->getEntityName();
  std::string secondName = second->getEntityName();

  if (secondName == "Wall") {
    updateData(world, first, second);
  } else {
    updateData(world, second, first);
  }
}
