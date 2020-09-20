//
// Created by Battary on 28.04.2020.
//

#pragma once

#include <string>

#include "IConstructor.h"

//Конструктор использующийся если подходящий конструктор не найден
class NothingConstructor : public IConstructor {
 public:
  NothingConstructor() = default;

  void constructObject(ecs::World&, std::string) override;

  ~NothingConstructor() override = default;
};
