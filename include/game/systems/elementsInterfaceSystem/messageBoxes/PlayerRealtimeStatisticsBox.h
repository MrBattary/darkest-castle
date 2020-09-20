//
// Created by Battary on 28.05.2020.
//

#pragma once
// Internal templates
#include "../IMessageBoxElement.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/components/StatisticsComponent.h"

class PlayerRealtimeStatisticsBox : public IMessageBoxElement {
 public:
  PlayerRealtimeStatisticsBox();

  void updateElement(ecs::World &) override;

  ~PlayerRealtimeStatisticsBox() override = default;
};
