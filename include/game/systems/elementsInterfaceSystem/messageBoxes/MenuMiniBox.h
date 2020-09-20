//
// Created by Battary on 28.07.2020.
//

#pragma once
// Internal templates
#include "../IMessageBoxElement.h"
// Systems
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/InterfaceUpdateSystem.h"
// Мини кнопка меню
class MenuMiniBox : public IMessageBoxElement {
 public:
  MenuMiniBox();

  void updateElement(ecs::World &) override;

  ~MenuMiniBox() override = default;
};
