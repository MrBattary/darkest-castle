// Created by Battary on 27.07.2020.
//

#pragma once
// Internal templates
#include "../IDialogBoxElement.h"
// Systems
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/PlayerMovementSystem.h"
#include "game/systems/EnemiesLogicSystem.h"
// Окно справки
class HelpBox : public IDialogBoxElement {
 public:
  explicit HelpBox(ecs::World&);

  void updateElement(ecs::World&) override;

  ~HelpBox() override = default;
};
