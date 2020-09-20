//
// Created by Battary on 11.06.2020.
//

#include "game/systems/keysKeyboardInputSystem/ContinueKey.h"

void ContinueKey::execute(ecs::World& world) {
  auto interfaceSystem = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSystem != nullptr) interfaceSystem->setCommand(name_);
}

ContinueKey::ContinueKey() {
  name_ = "Continue";
}
