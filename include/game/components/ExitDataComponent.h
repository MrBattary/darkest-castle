//
// Created by Battary on 01.07.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// ID:1001 Компонент-содержащий данные необходимые для телепортации кого-то на любую карту в позицию
class ExitDataComponent : public ecs::Component {
 public:
  int map_, toX_, toY_;

  explicit ExitDataComponent(int map = 0, int x = 0, int y = 0) : map_(map), toX_(x), toY_(y) {
    componentID_ = 1001;
  }

  ~ExitDataComponent() override = default;
};
