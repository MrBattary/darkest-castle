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
#include "game/components/SymbolComponent.h"
#include "game/components/StatsComponent.h"
#include "game/components/InventoryComponent.h"
// Средний противник
class BlueEnemy : public IEnemy {
 public:
  BlueEnemy() = default;

  void createEnemy(std::shared_ptr<Enemy>&) override;

  ~BlueEnemy() override = default;
};
