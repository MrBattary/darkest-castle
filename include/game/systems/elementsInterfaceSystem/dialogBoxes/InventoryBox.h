//
// Created by Battary on 27.07.2020.
//

#pragma once
// Internal templates
#include "../IDialogBoxElement.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/entities/ItemEntity.h"
// Components
#include "game/components/InventoryComponent.h"
#include "game/components/StatsComponent.h"
// Systems
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/PlayerMovementSystem.h"
#include "game/systems/EnemiesLogicSystem.h"
// Окно инвентаря
class InventoryBox : public IDialogBoxElement{
 private:
  void paintStat(const int);
 public:
  explicit InventoryBox(ecs::World&);

  void updateElement(ecs::World&) override;

  ~InventoryBox() override = default;
};
