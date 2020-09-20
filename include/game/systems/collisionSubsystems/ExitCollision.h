//
// Created by Battary on 26.05.2020.
//

#pragma once

#include <memory>

#include "ICollision.h"
// Entities
#include "game/entities/PlayerEntity.h"
// Components
#include "game/components/ControlComponent.h"
#include "game/components/ExitDataComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/EnemyLogicComponent.h"
// Systems
#include "game/systems/EntitiesDisplaySystem.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/elementsInterfaceSystem/dialogBoxes/EndLevelBox.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/LeaderboardBox.h"

class ExitCollision : public ICollision {
 private:
  void updateData(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);
 public:
  ExitCollision() = default;

  void updateSubsystem(ecs::World &, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) override;

  ~ExitCollision() override = default;
};
