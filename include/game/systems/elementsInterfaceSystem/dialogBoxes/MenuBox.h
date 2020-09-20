//
// Created by Battary on 29.06.2020.
//

#pragma once

// Internal templates
#include "../IDialogBoxElement.h"
// Systems
#include "game/systems/EntitiesDisplaySystem.h"
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/PlayerMovementSystem.h"
#include "game/systems/EnemiesLogicSystem.h"
// Окно меню/паузы
class MenuBox : public IDialogBoxElement {
 public:
  explicit MenuBox(ecs::World&);

  void updateElement(ecs::World&) override;

  ~MenuBox() override = default;
};
