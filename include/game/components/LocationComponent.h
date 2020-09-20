//
// Created by Battary on 25.03.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// ID:200 Компонент отвечает за положение по х и у сущности
class LocationComponent : public ecs::Component {
 public:
  int row_;
  int column_;

  explicit LocationComponent(int column = 0, int row = 0)
      : row_(row), column_(column) {
    componentID_ = 200;
  }

  ~LocationComponent() override = default;
};
