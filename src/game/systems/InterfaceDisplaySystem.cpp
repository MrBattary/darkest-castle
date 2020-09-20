//
// Created by Battary on 03.07.2020.
//

#include "game/systems/InterfaceDisplaySystem.h"
InterfaceDisplaySystem::InterfaceDisplaySystem() {
  setID(1001);
}

void InterfaceDisplaySystem::updateSystem(ecs::World& world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  for (auto& element : interfaceSys->elements_) {
    if (!element.second->getHide()) {
      interfaceSys->elements_.at(element.first)->displayElement();
    }
  }
}
