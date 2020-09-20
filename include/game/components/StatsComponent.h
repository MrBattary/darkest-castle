//
// Created by Battary on 04.07.2020.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "game/lib/ECS/ECS.h"

// ID:500 Компонент отвечает за характеристики (защита/урон итд)
class StatsComponent : public ecs::Component {
 private:
  class Stat {
   public:
    std::string name_;
    int value_;

    explicit Stat(std::string name = "", int value = 0) : name_(std::move(name)), value_(value) {}

    ~Stat() = default;
  };

 public:
  std::map<std::string, std::shared_ptr<Stat>> stats_;

  StatsComponent() {
    componentID_ = 500;
  }

  bool containStat(const std::string& statName) const {
    return stats_.count(statName) != 0;
  }

  void addStat(const std::string statName, int statValue) {
    if (!containStat(statName)) {
      stats_[statName] = std::make_shared<Stat>(statName, statValue);
      // stats_["+" + statName] = std::make_shared<Stat>("+" + statName, 0);
    }
  }

  std::shared_ptr<Stat> getStat(std::string name) {
    for (const auto& stat : stats_) {
      if (stat.first == name) {
        auto pointer = stats_.at(name);
        return std::dynamic_pointer_cast<Stat>(pointer);
      }
    }
    return nullptr;
  }

  ~StatsComponent() override = default;
};
