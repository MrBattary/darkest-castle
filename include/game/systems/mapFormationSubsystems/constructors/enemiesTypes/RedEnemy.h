//
// Created by Battary on 30.07.2020.
//

#pragma once
#include <memory>
// Internal template
#include "IEnemy.h"
// Entity
#include "game/entities/ItemEntity.h"
// Components
#include "game/components/EnemyLogicComponent.h"
#include "game/components/SymbolComponent.h"
#include "game/components/StatsComponent.h"
#include "game/components/InventoryComponent.h"
// Слабый противник
class RedEnemy : public IEnemy {
 public:
  RedEnemy() = default;

  void createEnemy(std::shared_ptr<Enemy>&) override;

  ~RedEnemy() override = default;
};
