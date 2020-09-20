//
// Created by Battary on 28.04.2020.
//

#pragma once

#include <tuple>
#include <string>
#include "game/lib/ECS/ECS.h"

// Шаблон конструкторов
class IConstructor {
 public:
  virtual void constructObject(ecs::World&, std::string) = 0;

  // Получить X и Y из конфигурационной строки
  static std::tuple<const int, const int> pullCoords(std::string);
  // Получить изображение объекта из конфигурационной строки
  static const std::string pullImage(std::string);

  virtual ~IConstructor() = default;
};
