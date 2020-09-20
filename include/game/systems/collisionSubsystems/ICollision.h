//
// Created by Battary on 27.03.2020.
//

#pragma once

#include <memory>

#include "game/lib/ECS/ECS.h"

//Шаблон подсистем коллизий
class ICollision {
 public:
  virtual void updateSubsystem(ecs::World &, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) = 0;

  virtual ~ICollision() = default;
};
