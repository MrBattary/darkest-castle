//
// Created by Battary on 29.07.2020.
//

#pragma once
#include <fstream>
#include <map>
#include <string>
#include <utility>
// Internal templates
#include "../IMessageBoxElement.h"
// Entities
#include "game/entities/PlayerEntity.h"
// Components
#include "game/components/StatisticsComponent.h"

// Таблица рекордов
class LeaderboardBox : public IMessageBoxElement {
 private:
  int openStream(std::ifstream& stream);
  int openStream(std::ofstream& stream);

 public:
  std::map<size_t, std::pair<size_t, std::string>> leaderboard_;

  LeaderboardBox();

  void updateElement(ecs::World&) override;

  ~LeaderboardBox() override = default;
};
