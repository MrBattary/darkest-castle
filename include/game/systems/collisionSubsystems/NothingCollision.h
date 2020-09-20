//
// Created by Battary on 28.03.2020.
//

#pragma once

#include <memory>

#include "ICollision.h"

//Подсистема необрабатываемых коллизий
class NothingCollision : public ICollision {
 public:
  NothingCollision() = default;

  void updateSubsystem(ecs::World&, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>) override;

  ~NothingCollision() override = default;
};
