//
// Created by Battary on 25.03.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

//Заданная сущность - сущность игрока
class Player : public ecs::Entity {
 public:
  Player() {
    setID(1);
    setEntityName("Player");
  }

  ~Player() override = default;
};
