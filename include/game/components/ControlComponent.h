//
// Created by Battary on 25.03.2020.
//

#pragma once

#include <map>
#include <string>

#include "game/lib/ECS/ECS.h"

// ID:300 Компонент отвечает за конфигурацию управления с клавиатуры
class ControlComponent : public ecs::Component {
 public:
  std::string current_;

  ControlComponent() {
    componentID_ = 300;
  }

  ~ControlComponent() override = default;
};
