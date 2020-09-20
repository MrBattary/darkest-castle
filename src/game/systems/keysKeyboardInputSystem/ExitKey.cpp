//
// Created by Battary on 26.05.2020.
//

#include "game/systems/keysKeyboardInputSystem/ExitKey.h"

void ExitKey::execute(ecs::World& world) {
  auto interfaceSystem = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSystem != nullptr) interfaceSystem->setCommand("Exit");
}

ExitKey::ExitKey() {
  name_ = "Exit";
}
