//
// Created by Battary on 30.07.2020.
//

#pragma once
#include <memory>

#include "game/entities/EnemyEntity.h"

// Шаблон конструкторов инвентарей
class IEnemy {
 public:
  virtual void createEnemy(std::shared_ptr<Enemy>&) = 0;

  virtual ~IEnemy() = default;
};
