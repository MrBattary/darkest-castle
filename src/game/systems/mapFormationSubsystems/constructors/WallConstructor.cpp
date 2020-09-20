//
// Created by Battary on 28.04.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/WallConstructor.h"

void WallConstructor::constructObject(ecs::World& world, std::string obj) {
  size_t wallID = world.createEntityAndReturnID<Wall>();
  auto wall = world.getEntity<Wall>(wallID);
  wall->addComponent<SymbolComponent>(0x23, "Wall10x16.png, align=center", 2);
  int x{0}, y{0};
  std::tie(x, y) = pullCoords(obj);
  wall->addComponent<LocationComponent>(x, y);
}
