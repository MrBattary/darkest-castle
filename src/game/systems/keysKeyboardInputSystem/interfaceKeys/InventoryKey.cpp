//
// Created by Battary on 27.07.2020.
//

#include "game/systems/keysKeyboardInputSystem/interfaceKeys/InventoryKey.h"

void InventoryKey::execute(ecs::World& world) {
  auto interfaceSystem = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSystem != nullptr) interfaceSystem->setCommand(name_);
}

InventoryKey::InventoryKey() {
  name_ = "Inventory";
}
