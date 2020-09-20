//
// Created by Battary on 27.07.2020.
//

#include "game/systems/elementsInterfaceSystem/dialogBoxes/HelpBox.h"

HelpBox::HelpBox(ecs::World& world) {
  setVariables(1, 2, "");

  name_ = "Help";
  reqUpdNumbers_ = {1};

  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  dialogKeys_[1] = std::make_pair("Close help:", keyboardSys->getKeyName("Help"));

  elementData_ = "Move up: " + keyboardSys->getKeyName("Move up") +
                 "\nMove down: " + keyboardSys->getKeyName("Move down") +
                 "\nMove left: " + keyboardSys->getKeyName("Move left") +
                 "\nMove right: " + keyboardSys->getKeyName("Move right") +
                 "\nInventory: " + keyboardSys->getKeyName("Inventory") +
                 "\nMenu: " + keyboardSys->getKeyName("Exit") +"\n";

  for (auto it = dialogKeys_.begin(); it != dialogKeys_.end(); ++it) {
    elementData_ += it->second.first + " " + (it->second.second);
    if (it != std::prev(dialogKeys_.end(), 1)) {
      elementData_ += "\n";
    }
  }

  calculateBoxSize(elementData_);

  expendable_ = false;
}

void HelpBox::updateElement(ecs::World& world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();

  if (interfaceSys->getCommand() == "Help") {
    expendable_ = true;
    interfaceSys->setCommand("");
  }
}
