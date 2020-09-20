//
// Created by Battary on 27.03.2020.
//

#pragma once

#include "game/lib/ECS/ECS.h"

// ID:400 Компонент отвечает за статистику игрока
class StatisticsComponent : public ecs::Component {
 public:
  size_t steps_;
  size_t coins_;

  explicit StatisticsComponent(size_t steps = 0, size_t coins = 0) : steps_(steps), coins_(coins) {
    componentID_ = 400;
  }

  ~StatisticsComponent() override = default;
};
