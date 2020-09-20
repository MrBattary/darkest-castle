//
// Created by Battary on 28.04.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/CoinConstructor.h"

void CoinConstructor::constructObject(ecs::World& world, std::string obj) {
  size_t coinID = world.createEntityAndReturnID<Coin>();
  auto coin = world.getEntity<Coin>(coinID);
  coin->addComponent<SymbolComponent>(0x24, "Coin8x8.png, align=center", 3);
  int x{0}, y{0};
  std::tie(x, y) = pullCoords(obj);
  coin->addComponent<LocationComponent>(x, y);
}
