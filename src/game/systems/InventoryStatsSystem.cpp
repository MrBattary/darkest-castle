//
// Created by Battary on 03.08.2020.
//

#include "game/systems/InventoryStatsSystem.h"
InventoryStatsSystem::InventoryStatsSystem() {
  setID(2);
  addProcessedComponents(500, 600);
}
void InventoryStatsSystem::updateSystem(ecs::World& world) {
  auto entities = world.getListEntities(getID());
  for (auto ent : entities) {
    auto entStatComp = ent->getComponent<StatsComponent>();
    std::map<std::string, int> entStatsBuff{};

    for (auto stat : entStatComp->stats_) {
      auto firstSymbol = stat.first.substr(0, 1);
      if (firstSymbol == "+") {
        auto statType = stat.first.substr(1);
        entStatsBuff[stat.first] = entStatComp->stats_.at(statType)->value_;
      }
    }

    auto entInvComp = ent->getComponent<InventoryComponent>();
    for (auto item : entInvComp->items_) {
      auto itemStatComp = item.second->getComponent<StatsComponent>();
      for (auto itemStat : itemStatComp->stats_) {
        auto statIt = entStatsBuff.find("+" + itemStat.first);
        statIt->second += itemStat.second->value_;
      }
    }

    for (auto buffStat : entStatsBuff) {
      auto statIt = entStatComp->stats_.find(buffStat.first);
      statIt->second->value_ = buffStat.second;
    }
  }
}
