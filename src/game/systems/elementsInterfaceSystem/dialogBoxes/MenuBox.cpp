//
// Created by Battary on 29.06.2020.
//

#include "game/systems/elementsInterfaceSystem/dialogBoxes/MenuBox.h"
MenuBox::MenuBox(ecs::World& world) {
  setVariables(31, 10, 18, 2, "");

  name_ = "Menu";
  reqUpdNumbers_ = {1};

  auto keyboardSys = world.getSystem<KeyboardInputSystem>();
  auto outputSys = world.getSystem<EntitiesDisplaySystem>();
  if (outputSys->getOutputMod()) {
    dialogKeys_[1] = std::make_pair("Graphic mod:", keyboardSys->getKeyName("Continue"));
  } else {
    dialogKeys_[1] = std::make_pair("Text mod:", keyboardSys->getKeyName("Continue"));
  }
  dialogKeys_[2] = std::make_pair("Continue:", keyboardSys->getKeyName("Stay"));
  dialogKeys_[3] = std::make_pair("Exit:", keyboardSys->getKeyName("Exit"));

  std::vector<std::string> phrases = {"Pausing...", "Have a rest", "Rest a bit", "Take a break"};
  auto phrase = rnd::RandomBetweenSizeT(0, phrases.size() - 1);
  elementData_ = phrases.at(phrase) + "\n\n";
  for (auto it = dialogKeys_.begin(); it != dialogKeys_.end(); ++it) {
    elementData_ += it->second.first + " " + (it->second.second);
    if (it != std::prev(dialogKeys_.end(), 1)) {
      elementData_ += "\n";
    }
  }

  calculateBoxSize(elementData_);

  expendable_ = false;
}

void MenuBox::updateElement(ecs::World& world) {
  auto interfaceSys = world.getSystem<InterfaceUpdateSystem>();
  auto outputSys = world.getSystem<EntitiesDisplaySystem>();

  if (interfaceSys->getCommand() == "Exit") {
    world.terminateApplication();
  }
  if (interfaceSys->getCommand() == "Stay" || interfaceSys->getCommand() == "Continue") {
    if (interfaceSys->getCommand() == "Continue") {
      outputSys->switchMod();
    }
    expendable_ = true;
    interfaceSys->setCommand("");
  }
}
