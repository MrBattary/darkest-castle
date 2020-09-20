//
// Created by Battary on 28.07.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/InventoryMiniBox.h"
InventoryMiniMox::InventoryMiniMox() {
  setVariables(68, 24, 12, 1, "");
  name_ = "Inventory Mini";
  reqUpdNumbers_ = {1, 2};
  expendable_ = false;
}

void InventoryMiniMox::updateElement(ecs::World& world) {
  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  if (!interfaceSys->containElement("Inventory") || interfaceSys->getElementExpendableStatus("Inventory")) {
    elementData_ = "Inventory: " + keyboardSys->getKeyName("Inventory");
  } else {
    elementData_ = "[color=yellow]Inventory: " + keyboardSys->getKeyName("Inventory") + "[/color]";
  }
}
