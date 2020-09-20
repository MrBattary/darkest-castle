//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// Заданная сущность - сущность выхода с уровня
class Exit : public ecs::Entity {
 public:
  Exit() {
    setEntityName("Exit");
  }

  ~Exit() override = default;
};
