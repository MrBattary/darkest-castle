//
// Created by Battary on 04.07.2020.
//

#pragma once

#include <map>
#include <string>
#include <memory>
#include "game/lib/ECS/ECS.h"
#include "game/entities/ItemEntity.h"

// ID:600 Компонент отвечает за инвентарь
class InventoryComponent : public ecs::Component {
 public:
  std::map<std::string, std::shared_ptr<Item>> items_;

  InventoryComponent() {
    componentID_ = 600;
  }

  ~InventoryComponent() override = default;
};
