//
// Created by Battary on 27.04.2020.
//

#pragma once

#include <iostream>

namespace ecs {
//Компонент-шаблон
class Component {
 protected:
  size_t componentID_{0};

 public:
  //Получить уникальный ID компонента
  size_t getComponentID() {
    return componentID_;
  }
  virtual ~Component() = default;
};
}  // namespace ecs
