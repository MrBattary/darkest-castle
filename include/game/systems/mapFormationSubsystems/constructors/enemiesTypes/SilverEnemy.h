//
// Created by Battary on 04.08.2020.
//

#pragma once
#include <memory>
// Internal template
#include "IEnemy.h"
// Entity
#include "game/entities/ItemEntity.h"
// Components
#include "game/components/EnemyLogicComponent.h"
#include "game/components/InventoryComponent.h"
#include "game/components/StatsComponent.h"
#include "game/components/SymbolComponent.h"
// Элитный противник
class SilverEnemy : public IEnemy {
 public:
  SilverEnemy() = default;

  void createEnemy(std::shared_ptr<Enemy>&) override;

  ~SilverEnemy() override = default;
};
