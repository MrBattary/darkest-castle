//
// Created by Battary on 25.05.2020.
//

#pragma once

#include <string>
#include <utility>
#include <vector>
#include "game/lib/Random/Random.h"
#include "IMap.h"
// Entities
#include "game/entities/PlayerEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/DirectionComponent.h"
#include "game/components/PreviousLocationComponent.h"

// Класс отвечает за внутреннюю генерацию карты по особым правилам
class GenerateMap : IMap {
 private:
  std::vector<std::string> objects_{};
  std::vector<std::pair<int, int>> forbiddenCords_{};
  int nextMap_{};
  bool enterFromRight_{false};
  bool exitBuilt_{false};

  void addForbiddenTypeH(int, int);
  bool findForbidden(int, int) const;
  void takeMapNumbers(std::string &, std::string &);
  void buildObject(std::string, int, int, std::string);
  void buildOneSideBorder(int, int, int, int, int);
  void buildSideBorders(ecs::World &);
  void buildTopAndBottomBorders();
  void fillTheSpace();

 public:
  explicit GenerateMap(size_t);

  std::vector<std::string> BuildMap(ecs::World &) override;

  ~GenerateMap() override = default;
};
