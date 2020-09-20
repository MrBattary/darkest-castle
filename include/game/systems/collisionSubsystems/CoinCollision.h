//
// Created by Battary on 27.03.2020.
//

#pragma once

#include <memory>

#include "ICollision.h"
#include "game/components/StatisticsComponent.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeLogBox.h"

//Подсистема коллизии с монетками
class CoinCollision : public ICollision {
 private:
  void updateData(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);

 public:
  CoinCollision() = default;

  void updateSubsystem(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) override;

  ~CoinCollision() override = default;
};
