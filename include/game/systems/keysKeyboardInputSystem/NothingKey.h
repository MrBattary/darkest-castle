//
// Created by Battary on 26.05.2020.
//

#pragma once

#include "IKey.h"

// Класс-затычка сообщения
class NothingKey : public IKey {
 public:
  NothingKey() = default;

  void execute(ecs::World&) override;

  ~NothingKey() override = default;
};
