//
// Created by Battary on 03.08.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"
// Entity
#include "game/entities/ItemEntity.h"
// Components
#include "game/components/InventoryComponent.h"
#include "game/components/StatsComponent.h"

class InventoryStatsSystem : public ecs::System {
 public:
  InventoryStatsSystem();

  void updateSystem(ecs::World&) override;

  ~InventoryStatsSystem() override = default;
};
