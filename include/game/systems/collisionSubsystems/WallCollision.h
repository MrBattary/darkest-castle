//
// Created by Battary on 27.04.2020.
//

#pragma once

#include <memory>

#include "ICollision.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/DirectionComponent.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeLogBox.h"

class WallCollision : public ICollision {
 private:
  void updateData(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);

 public:
  WallCollision() = default;

  void updateSubsystem(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) override;

  ~WallCollision() override = default;
};
