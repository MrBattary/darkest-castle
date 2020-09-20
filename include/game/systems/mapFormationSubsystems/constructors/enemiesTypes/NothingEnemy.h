//
// Created by Battary on 30.07.2020.
//

#pragma once
#include <memory>
// Internal template
#include "IEnemy.h"

// Тип-затычка
class NothingEnemy : public IEnemy {
 public:
  NothingEnemy() = default;

  void createEnemy(std::shared_ptr<Enemy>&) override;

  ~NothingEnemy() override = default;
};
