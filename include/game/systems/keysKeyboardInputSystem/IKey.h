//
// Created by Battary on 26.05.2020.
//

#pragma once

#include <string>

#include "game/lib/ECS/ECS.h"

// Класс-шаблон сообщения
class IKey {
 public:
  std::string name_ {};

  virtual void execute(ecs::World&) = 0;

  virtual ~IKey() = default;
};
