//
// Created by Battary on 28.07.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/MenuMiniBox.h"

MenuMiniBox::MenuMiniBox() {
  setVariables(71, 0, 9, 1, "");
  name_ = "Menu Mini";
  reqUpdNumbers_ = {1, 2};
  expendable_ = false;
}

void MenuMiniBox::updateElement(ecs::World& world) {
  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  if (!interfaceSys->containElement("Menu") || interfaceSys->getElementExpendableStatus("Menu")) {
    elementData_ = "Menu: " + keyboardSys->getKeyName("Exit");
  } else {
    elementData_ = "[color=yellow]Menu: " + keyboardSys->getKeyName("Exit") + "[/color]";
  }
}
