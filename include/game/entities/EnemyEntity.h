//
// Created by Battary on 30.07.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// Заданная сущность - шаблон для врагов
class Enemy : public ecs::Entity {
 public:
  Enemy() = default;

  ~Enemy() override = default;
};
