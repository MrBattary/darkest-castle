//
// Created by Battary on 28.04.2020.
//

#pragma once
#include <string>

#include "IConstructor.h"
// Entity
#include "game/entities/CoinEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/SymbolComponent.h"

//Конструктор создающий монетки
class CoinConstructor : public IConstructor {
 public:
  CoinConstructor() = default;

  void constructObject(ecs::World&, std::string) override;

  ~CoinConstructor() override = default;
};
