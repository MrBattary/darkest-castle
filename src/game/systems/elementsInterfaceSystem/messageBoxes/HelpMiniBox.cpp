//
// Created by Battary on 28.07.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/HelpMiniBox.h"
HelpMiniBox::HelpMiniBox() {
  setVariables(62, 0, 7, 1, "");
  name_ = "Help Mini";
  reqUpdNumbers_ = {1, 2};
  expendable_ = false;
}
void HelpMiniBox::updateElement(ecs::World& world) {
  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  if (!interfaceSys->containElement("Help") || interfaceSys->getElementExpendableStatus("Help")) {
    elementData_ = "Help: " + keyboardSys->getKeyName("Help");
  } else {
    elementData_ = "[color=yellow]Help: " + keyboardSys->getKeyName("Help") + "[/color]";
  }
}
