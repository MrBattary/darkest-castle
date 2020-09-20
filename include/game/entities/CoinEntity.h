//
// Created by Battary on 27.03.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

//Заданная сущность - сущность монетки
class Coin : public ecs::Entity {
 public:
  Coin() {
    setEntityName("Coin");
  }

  ~Coin() override = default;
};
