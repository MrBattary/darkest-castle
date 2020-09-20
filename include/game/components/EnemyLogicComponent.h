//
// Created by Battary on 30.07.2020.
//

#pragma once
#include <string>
#include <utility>
#include <vector>

#include "game/lib/ECS/ECS.h"

// ID:700 Компонент отвечает за настройки логики у врагов
class EnemyLogicComponent : public ecs::Component {
 public:
  std::vector<std::pair<int, int>> steps_{};
  std::vector<std::string> hostiles_{};
  size_t aggroRange_;

  explicit EnemyLogicComponent(size_t range = 1) : aggroRange_(range) {
    componentID_ = 700;
  }

  ~EnemyLogicComponent() override = default;
};
