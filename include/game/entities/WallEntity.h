//
// Created by Battary on 27.04.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

//Заданная сущность - сущность стены
class Wall : public ecs::Entity {
 public:
  Wall() {
    setEntityName("Wall");
  }

  ~Wall() override = default;
};
