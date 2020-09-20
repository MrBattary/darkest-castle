//
// Created by Battary on 28.07.2020.
//

#pragma once
// Internal templates
#include "../IMessageBoxElement.h"
// Systems
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/InterfaceUpdateSystem.h"
// Мини кнопка помощи
class HelpMiniBox : public IMessageBoxElement {
 public:
  HelpMiniBox();

  void updateElement(ecs::World &) override;

  ~HelpMiniBox() override = default;
};
