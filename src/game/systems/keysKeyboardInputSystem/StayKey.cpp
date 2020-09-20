//
// Created by Battary on 28.05.2020.
//

#include "game/systems/keysKeyboardInputSystem/StayKey.h"

void StayKey::execute(ecs::World& world) {
  auto interfaceSystem = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSystem != nullptr) interfaceSystem->setCommand(name_);
}

StayKey::StayKey() {
  name_ = "Stay";
}
