//
// Created by Battary on 25.05.2020.
//

#pragma once

#include <string>
#include <vector>

#include "game/lib/ECS/ECS.h"

// Класс-шаблон для классов-методов
class IMap {
 public:
  virtual std::vector<std::string> BuildMap(ecs::World&) = 0;

  virtual ~IMap() = default;
};
