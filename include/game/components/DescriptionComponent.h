//
// Created by Battary on 11.06.2020.
//

#pragma once

#include <string>
#include <utility>

#include "game/lib/ECS/ECS.h"

// ID:1000 Компонент-описание для всего
class DescriptionComponent : public ecs::Component {
 public:
  std::string data_;

  explicit DescriptionComponent(std::string str = "") : data_(std::move(str)) {
    componentID_ = 1000;
  }

  ~DescriptionComponent() override = default;
};
