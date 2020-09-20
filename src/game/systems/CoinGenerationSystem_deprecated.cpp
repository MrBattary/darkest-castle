//
// Created by Battary on 27.03.2020.
//

#include "game/systems/CoinGenerationSystem_deprecated.h"

CoinGenerationSystem::CoinGenerationSystem(size_t startCoins = 0, size_t nextCoin = 0, size_t maxCoins = 1)
    : startCoins_(startCoins), nextCoin_(nextCoin), maxCoins_(maxCoins) {
  setID(900);
  addProcessedComponents(0);
}

bool CoinGenerationSystem::cordsExist(int row, int column) {
  for (auto &coin : internalCoinsList_) {
    if (coin.second.first == row && coin.second.second == column) {
      return true;
    }
  }
  return false;
}

void CoinGenerationSystem::updateInternalCoinsList(ecs::World &world) {
  bool listChecked{true};

  do {
    listChecked = true;
    for (auto &list : internalCoinsList_) {
      if (!world.containEntity(list.first)) {
        deleteCoinFromInternalCoinsList(list.first);
        listChecked = false;
        break;
      }
    }
  } while (!listChecked);
}

void CoinGenerationSystem::deleteCoinFromInternalCoinsList(size_t coinID) {
  internalCoinsList_.erase(coinID);
}

void CoinGenerationSystem::createCoin(ecs::World &world) {
  auto newCoin = std::make_shared<Coin>();
  int row = 0;
  int column = 0;

  do {
    row = rnd::RandomBetweenInt(1, 24);
    column = rnd::RandomBetweenInt(0, 79);
  } while (cordsExist(row, column));

  newCoin->addComponent<SymbolComponent>(0x24, "Coin8x8.png, align=center", 3);
  newCoin->addComponent<LocationComponent>(row, column);

  size_t idNewCoin = world.addEntity(std::move(newCoin));
  internalCoinsList_[idNewCoin] = std::make_pair(row, column);
}

void CoinGenerationSystem::updateSystem(ecs::World &world) {
  updateInternalCoinsList(world);

  if (startCoins_) {
    for (size_t i = 0; i < startCoins_; i++) {
      createCoin(world);
    }
    startCoins_ = 0;
    world.updateWorldList();
  }

  if (internalCoinsList_.size() < maxCoins_) {
    if (nextCoin_ == 0 || internalCoinsList_.empty()) {
      createCoin(world);
      nextCoin_ = rnd::RandomBetweenSizeT(30, 50);
      world.updateWorldList();
    }
    nextCoin_ -= 1;
  }
}
