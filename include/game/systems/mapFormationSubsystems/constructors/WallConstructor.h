//
// Created by Battary on 28.04.2020.
//

#pragma once

#include <string>

#include "IConstructor.h"
// Entity
#include "game/entities/WallEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/SymbolComponent.h"

//Конструктор создающий стены
class WallConstructor : public IConstructor {
 public:
  WallConstructor() = default;

  void constructObject(ecs::World&, std::string) override;

  ~WallConstructor() override = default;
};
