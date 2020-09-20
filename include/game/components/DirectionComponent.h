//
// Created by Battary on 01.07.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// ID:202 Компонент отвечает за направление движения сущности
class DirectionComponent : public ecs::Component {
 public:
  enum Direction { UPWARD, RIGHTWARD, DOWNWARD, LEFTWARD, NOWHERE };

  Direction direction_{};

  DirectionComponent() {
    componentID_ = 202;
  }

  ~DirectionComponent() override = default;
};
