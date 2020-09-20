//
// Created by Battary on 27.04.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// ID:201 Компонент отвечает за положение по х и у сущности
class PreviousLocationComponent : public ecs::Component {
 public:
  int rowPrevious_;
  int columnPrevious_;

  explicit PreviousLocationComponent(int row = 0, int column = 0) : rowPrevious_(row), columnPrevious_(column) {
    componentID_ = 201;
  }

  ~PreviousLocationComponent() override = default;
};
