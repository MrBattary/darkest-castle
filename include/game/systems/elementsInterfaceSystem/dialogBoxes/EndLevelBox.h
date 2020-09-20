//
// Created by Battary on 29.05.2020.
//

#pragma once
// Internal templates
#include "../IDialogBoxElement.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeStatisticsBox.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/LeaderboardBox.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/entities/ExitEntity.h"
// Components
#include "game/components/PreviousLocationComponent.h"
#include "game/components/StatisticsComponent.h"
// Systems
#include "game/systems/EntitiesDisplaySystem.h"
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/MapFormationSystem.h"
#include "game/systems/PlayerMovementSystem.h"
#include "game/systems/EnemiesLogicSystem.h"
// Окно которое появлется при выходе с уровня
class EndLevelBox : public IDialogBoxElement {
 private:
  int tpToX_{0};
  int tpToY_{0};
  int nextMap_{0};
 public:
  explicit EndLevelBox(ecs::World&, int, int, int);

  void updateElement(ecs::World&) override;

  ~EndLevelBox() override = default;
};
