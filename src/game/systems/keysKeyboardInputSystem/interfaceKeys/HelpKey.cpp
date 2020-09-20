//
// Created by Battary on 27.07.2020.
//

#include "game/systems/keysKeyboardInputSystem/interfaceKeys/HelpKey.h"

void HelpKey::execute(ecs::World& world) {
  auto interfaceSystem = world.getSystem<InterfaceUpdateSystem>();
  if (interfaceSystem != nullptr) interfaceSystem->setCommand(name_);
}

HelpKey::HelpKey() {
  name_ = "Help";
}
