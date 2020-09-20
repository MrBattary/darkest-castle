//
// Created by Battary on 25.05.2020.
//

#include "game/systems/mapFormationSubsystems/GenerateMap.h"

GenerateMap::GenerateMap(size_t nMap) : nextMap_(nMap) {}

void GenerateMap::buildObject(std::string symbol, int column, int row, std::string other) {
  std::string object, xStr, yStr;
  if (column < 10) {
    xStr = "0" + std::to_string(column);
  } else {
    xStr = std::to_string(column);
  }
  if (row < 10) {
    yStr = "0" + std::to_string(row);
  } else {
    yStr = std::to_string(row);
  }
  object += symbol + "AxisX" + xStr + "AxisY" + yStr + other;
  objects_.push_back(object);
}

void GenerateMap::takeMapNumbers(std::string &next, std::string &prev) {
  if (nextMap_ > -9) {
    int buffNum = 0 - nextMap_;
    next = "-0" + std::to_string(buffNum + 1);
    prev = "-0" + std::to_string(buffNum - 1);
    return;
  }
  if (nextMap_ == -9) {
    int buffNum = 0 - nextMap_;
    next = "-0" + std::to_string(buffNum + 1);
    prev = std::to_string(nextMap_ - 1);
    return;
  }
  if (nextMap_ < -9) {
    next = std::to_string(nextMap_);
    prev = std::to_string(nextMap_);
    return;
  }
}

void GenerateMap::buildOneSideBorder(int rowPlayer, int columnPrevPlayer, int rowPrevPlayer, int columnFst,
                                     int columnSnd) {
  std::string mapNumPrev, mapNumNext;
  takeMapNumbers(mapNumNext, mapNumPrev);
  std::string prev, next;
  if (enterFromRight_) {
    prev = "<";
    next = ">";
  } else {
    prev = ">";
    next = "<";
  }
  for (int y = 2; y < 23; y++) {
    if (y == rowPlayer) {
      std::string rowPrev, colPrev;
      if (rowPrevPlayer < 10) {
        rowPrev = "0" + std::to_string(rowPrevPlayer);
      } else {
        rowPrev = std::to_string(rowPrevPlayer);
      }
      if (columnPrevPlayer < 10) {
        colPrev = "0" + std::to_string(columnPrevPlayer);
      } else {
        colPrev = std::to_string(columnPrevPlayer);
      }

      buildObject(prev, columnFst, y, "Map" + mapNumPrev + "ToX" + colPrev + "ToY" + rowPrev);
      addForbiddenTypeH(columnFst, y);
    } else {
      buildObject("#", columnFst, y, "");
    }
  }
  for (int y = 2; y < 23; y++) {
    int whatBuild = rnd::RandomBetweenInt(0, 22 - y);
    if (!whatBuild && !exitBuilt_) {
      std::string rowNext, colNext;
      if (y < 10) {
        rowNext = "0" + std::to_string(y);
      } else {
        rowNext = std::to_string(y);
      }
      if (enterFromRight_) {
        colNext = "01";
      } else {
        colNext = "78";
      }

      buildObject(next, columnSnd, y, "Map" + mapNumNext + "ToX" + colNext + "ToY" + rowNext);
      addForbiddenTypeH(columnSnd, y);
      exitBuilt_ = true;
    } else {
      buildObject("#", columnSnd, y, "");
    }
  }
}

void GenerateMap::buildSideBorders(ecs::World &world) {
  auto playerEnt = world.getEntity<Player>(1);
  auto playerCordsComp = playerEnt->getComponent<LocationComponent>();
  auto playerPrevCordsComp = playerEnt->getComponent<PreviousLocationComponent>();
  auto playerDirectionComp = playerEnt->getComponent<DirectionComponent>();

  if (playerDirectionComp->direction_ == DirectionComponent::RIGHTWARD) {
    enterFromRight_ = true;
  }
  if (playerDirectionComp->direction_ == DirectionComponent::LEFTWARD) {
    enterFromRight_ = false;
  }

  if (enterFromRight_) {
    buildOneSideBorder(playerCordsComp->row_, playerPrevCordsComp->columnPrevious_, playerPrevCordsComp->rowPrevious_,
                       0, 79);
  } else {
    buildOneSideBorder(playerCordsComp->row_, playerPrevCordsComp->columnPrevious_, playerPrevCordsComp->rowPrevious_,
                       79, 0);
  }
}

void GenerateMap::buildTopAndBottomBorders() {
  for (int x = 0; x < 80; x++) {
    buildObject("#", x, 1, "");
  }
  for (int x = 0; x < 80; x++) {
    buildObject("#", x, 23, "");
  }
}

void GenerateMap::fillTheSpace() {
  // TODO(Battary): Улучшить генерацию
  bool strongEnemy{false};
  for (int x = 1; x < 79; x++) {
    for (int y = 2; y < 23; y++) {
      auto choice = rnd::RandomBetweenInt(1, 1000);

      if (choice >= 1 && choice <= 120) {
        if (findForbidden(x, y)) {
          buildObject("#", x, y, "");
        }
      }
      if (choice >= 121 && choice <= 140) {
        buildObject("$", x, y, "");
      }
      if (choice >= 141 && choice <= 144) {
        buildObject("ERed", x, y, "");
      }
      if (choice >= 145 && choice <= 146) {
        buildObject("EBlu", x, y, "");
      }
      if (choice >= 147 && choice <= 150 && !strongEnemy) {
        buildObject("ESil", x, y, "");
        strongEnemy = true;
      }
    }
  }
}

std::vector<std::string> GenerateMap::BuildMap(ecs::World &world) {
  buildSideBorders(world);
  buildTopAndBottomBorders();
  fillTheSpace();
  return objects_;
}

bool GenerateMap::findForbidden(int x, int y) const {
  auto checked = std::make_pair(x, y);
  for (auto &cord : forbiddenCords_) {
    if (cord == checked) {
      return false;
    }
  }
  return true;
}

void GenerateMap::addForbiddenTypeH(int x, int y) {
  forbiddenCords_.push_back(std::make_pair(x + 1, y - 1));
  forbiddenCords_.push_back(std::make_pair(x + 1, y));
  forbiddenCords_.push_back(std::make_pair(x + 1, y + 1));
  forbiddenCords_.push_back(std::make_pair(x - 1, y - 1));
  forbiddenCords_.push_back(std::make_pair(x - 1, y));
  forbiddenCords_.push_back(std::make_pair(x - 1, y + 1));
}
