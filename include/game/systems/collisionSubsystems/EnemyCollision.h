//
// Created by Battary on 03.08.2020.
//

#pragma once

#include <memory>
#include "ICollision.h"
// Entities
#include "game/entities/ItemEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/DirectionComponent.h"
#include "game/components/StatsComponent.h"
#include "game/components/InventoryComponent.h"
// Systems
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/elementsInterfaceSystem/dialogBoxes/EndGameBox.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/LeaderboardBox.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeLogBox.h"

// Столкновение персонажа с врагом
class EnemyCollision : public ICollision {
 private:
  void updateData(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);
 public:
  EnemyCollision() = default;

  void updateSubsystem(ecs::World &, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) override;

  ~EnemyCollision() override = default;
};
