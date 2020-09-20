//
// Created by Battary on 26.05.2020.
//

#pragma once

#include <string>

#include "IConstructor.h"
// Entity
#include "game/entities/ExitEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/SymbolComponent.h"
#include "game/components/ExitDataComponent.h"

//Конструктор создающий выходы
class ExitConstructor : public IConstructor {
 private:
  static int pullData(std::string, std::string);
 public:
  ExitConstructor() = default;

  void constructObject(ecs::World&, std::string) override;

  ~ExitConstructor() override = default;
};
