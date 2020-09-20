//
// Created by Battary on 27.03.2020.
//

#include "game/systems/collisionSubsystems/CoinCollision.h"

void CoinCollision::updateData(ecs::World &world, std::shared_ptr<ecs::Entity> first,
                               std::shared_ptr<ecs::Entity> second) {
  world.purgeEntity(first->getID());
  auto stat = second->getComponent<StatisticsComponent>();
  stat->coins_ = ++stat->coins_;

  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  auto logBox = interfaceSys->getElement<PlayerRealtimeLogBox>();
  logBox->addData("Coin found ");
}

void CoinCollision::updateSubsystem(ecs::World &world, std::shared_ptr<ecs::Entity> first,
                                    std::shared_ptr<ecs::Entity> second) {
  std::string firstName = first->getEntityName();
  std::string secondName = second->getEntityName();

  if (firstName == "Coin") {
    updateData(world, first, second);
  } else {
    updateData(world, second, first);
  }
  world.updateWorldList();
}
