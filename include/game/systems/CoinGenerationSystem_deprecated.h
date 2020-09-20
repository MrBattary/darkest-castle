//
// Created by Battary on 27.03.2020.
//

#pragma once

#include <map>
#include <utility>

#include "game/lib/ECS/ECS.h"
#include "game/lib/Random/Random.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/SymbolComponent.h"
// Entities
#include "game/entities/CoinEntity.h"

//Система генерации новых монет
class CoinGenerationSystem : public ecs::System {
 private:
  std::map<size_t, std::pair<int, int>> internalCoinsList_ {};
  size_t startCoins_;
  size_t nextCoin_;
  size_t maxCoins_;

  bool cordsExist(int, int);
  void createCoin(ecs::World &);
  void updateInternalCoinsList(ecs::World &);
  void deleteCoinFromInternalCoinsList(size_t);

 public:
  CoinGenerationSystem(size_t, size_t, size_t);

  void updateSystem(ecs::World&) override;

  ~CoinGenerationSystem() override = default;
};
