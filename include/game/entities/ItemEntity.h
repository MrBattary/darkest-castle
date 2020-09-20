//
// Created by Battary on 04.07.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// Заданная сущность - сущность предмета
class Item : public ecs::Entity {
 public:
  Item() {
    setEntityName("Item");
  }

  ~Item() override = default;
};
