//
// Created by Battary on 26.03.2020.
//

#pragma once

#include <string>

#include "game/lib/ECS/ECS.h"

// ID:100 Компонент отвечает за символ, которым отображается сущность
class SymbolComponent : public ecs::Component {
 public:
  int symbol_;
  std::string spriteData_;
  int layer_;

  explicit SymbolComponent(int symbol = 0, std::string spriteData = "", int layer = 1)
      : symbol_(symbol), spriteData_(spriteData), layer_(layer) {
    componentID_ = 100;
  }

  ~SymbolComponent() override = default;
};
