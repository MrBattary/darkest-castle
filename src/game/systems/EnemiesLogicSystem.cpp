//
// Created by Battary on 30.07.2020.
//

#include "game/systems/EnemiesLogicSystem.h"
EnemiesLogicSystem::EnemiesLogicSystem() {
  setID(300);
  addProcessedComponents(700);
}

void EnemiesLogicSystem::updateSystem(ecs::World& world) {
  fillEntitiesLocation(world);
  auto entities = world.getListEntities(getID());
  for (auto& enemy : entities) {
    auto targetID = targetSelection(world, enemy);
    auto listOfHostilesForCurrentEnemy = cutEnemies(world, enemy);
    if (targetID) {
      // Если цель найдена сброс старого пути и просчет пути до координат цели
      auto target = world.getEntity<ecs::Entity>(targetID);
      auto targetLocationComp = target->getComponent<LocationComponent>();
      auto targetPrevLocationComp = target->getComponent<PreviousLocationComponent>();
      auto targetDirectionComp = target->getComponent<DirectionComponent>();
      auto targetLocation = std::make_pair(targetLocationComp->column_, targetLocationComp->row_);
      std::pair<int, int> targetLocationPrev{};
      if (targetDirectionComp->direction_ == DirectionComponent::UPWARD ||
          targetDirectionComp->direction_ == DirectionComponent::DOWNWARD) {
        targetLocationPrev = std::make_pair(targetLocationComp->column_, targetPrevLocationComp->rowPrevious_);
      }
      if (targetDirectionComp->direction_ == DirectionComponent::LEFTWARD ||
          targetDirectionComp->direction_ == DirectionComponent::RIGHTWARD) {
        targetLocationPrev = std::make_pair(targetPrevLocationComp->columnPrevious_, targetLocationComp->row_);
      }

      auto enemyLogicComp = enemy->getComponent<EnemyLogicComponent>();
      auto enemyLocComp = enemy->getComponent<LocationComponent>();
      auto enemyLocCompPrev = enemy->getComponent<PreviousLocationComponent>();
      auto enemyLocPrev = std::make_pair(enemyLocCompPrev->columnPrevious_, enemyLocCompPrev->rowPrevious_);
      auto enemyLoc = std::make_pair(enemyLocComp->column_, enemyLocComp->row_);

      // Проверка местоположения цели
      if (std::find(entitiesLocation_.begin(), entitiesLocation_.end(), targetLocation) == entitiesLocation_.end()) {
        // Если цель в допустимой точке
        enemyLogicComp->steps_.clear();
        buildingPathToTarget(enemy, targetLocation);
      } else {
        // Если цель атаковала самостоятельно
        if (enemyLoc == targetLocation || enemyLocPrev == targetLocation) {
          enemyLogicComp->steps_.clear();
          enemyLogicComp->steps_.push_back(std::make_pair(enemyLocComp->column_, enemyLocComp->row_));
        } else {
          // Просчет пути до последеней допустимой точки цели
          enemyLogicComp->steps_.clear();
          buildingPathToTarget(enemy, targetLocationPrev);
          // Аварийный просчет
          if (enemyLogicComp->steps_.empty()) {
            targetID = 0;
          }
        }
      }
    }
    if (!targetID) {
      auto logicComp = enemy->getComponent<EnemyLogicComponent>();
      if (logicComp->steps_.empty()) {
        // Просчет пути до случайной точки в аггро зоне
        bool possibleCords{false};
        auto enemyLocationComp = enemy->getComponent<LocationComponent>();
        auto enemyLogicComp = enemy->getComponent<EnemyLogicComponent>();
        std::pair<int, int> enemyLocation{enemyLocationComp->column_, enemyLocationComp->row_};
        auto aggroRange = static_cast<int>(enemyLogicComp->aggroRange_);
        do {
          // TODO(Battary): Переработать
          auto columnR = rnd::RandomBetweenInt(enemyLocation.first - aggroRange, enemyLocation.first + aggroRange);
          auto rowR = rnd::RandomBetweenInt(enemyLocation.second - aggroRange, enemyLocation.second + aggroRange);
          std::pair<int, int> randomCords{columnR, rowR};
          auto findRandomPoint = std::find(entitiesLocation_.begin(), entitiesLocation_.end(), randomCords);
          if (findRandomPoint == entitiesLocation_.end()) {
            buildingPathToTarget(enemy, std::make_pair(columnR, rowR));
            possibleCords = true;
          }
        } while (!possibleCords);
      }
    }
    entitiesLocation_.insert(entitiesLocation_.end(), listOfHostilesForCurrentEnemy.begin(),
                             listOfHostilesForCurrentEnemy.end());
    moveEnemy(enemy);
  }
}

void EnemiesLogicSystem::fillEntitiesLocation(ecs::World& world) {
  entitiesLocation_.clear();
  auto entitiesList = world.getEntitiesInRange(0, 0);
  for (auto entity : entitiesList) {
    if (entity->getEntityName() != "Coin") {
      auto entityLocationComp = entity->getComponent<LocationComponent>();
      entitiesLocation_.push_back(std::make_pair(entityLocationComp->column_, entityLocationComp->row_));
    }
  }
}

// Выбор ближайшего врага для атаки
size_t EnemiesLogicSystem::targetSelection(ecs::World& world, std::shared_ptr<ecs::Entity> enemy) {
  auto allHostilesID = confrontationWithHostiles(world, enemy);
  size_t targetID{0};
  int maxRange{999};
  if (!allHostilesID.empty()) {
    for (auto hostileID : allHostilesID) {
      auto hostile = world.getEntity<ecs::Entity>(hostileID);
      if (hostile != nullptr) {
        auto enemyLocationComp = enemy->getComponent<LocationComponent>();
        auto hostileLocationComp = hostile->getComponent<LocationComponent>();
        auto currentRange = abs(enemyLocationComp->column_ - hostileLocationComp->column_) +
                            abs(enemyLocationComp->row_ - hostileLocationComp->row_);
        if (currentRange < maxRange) {
          maxRange = currentRange;
          targetID = hostileID;
        }
      }
    }
  }
  return targetID;
}

// Составление списка координат всех сущностей враждебных проверяемой сущности
std::vector<std::pair<int, int>> EnemiesLogicSystem::cutEnemies(ecs::World& world, std::shared_ptr<ecs::Entity> enemy) {
  auto logicComp = enemy->getComponent<EnemyLogicComponent>();

  std::vector<std::pair<int, int>> buff{};
  for (auto hostile : logicComp->hostiles_) {
    for (auto ent : world.getEntitiesInRange(0, 0)) {
      if (ent->getEntityName() == hostile) {
        auto entLocComp = ent->getComponent<LocationComponent>();
        auto cordsIt = std::find(entitiesLocation_.begin(), entitiesLocation_.end(),
                                 std::make_pair(entLocComp->column_, entLocComp->row_));
        if (cordsIt != entitiesLocation_.end()) {
          std::move(cordsIt, cordsIt + 1, std::back_inserter(buff));
          entitiesLocation_.erase(cordsIt, cordsIt + 1);
        }
      }
    }
  }

  return buff;
}

// Составление списка ID всех сущностей, которые пересекаются с зоной атаки конкретной враждебной сущности
std::vector<size_t> EnemiesLogicSystem::confrontationWithHostiles(ecs::World& world,
                                                                  std::shared_ptr<ecs::Entity> enemy) {
  auto logicComp = enemy->getComponent<EnemyLogicComponent>();
  std::vector<size_t> allHostilesID{};

  for (auto hostile : logicComp->hostiles_) {
    auto hostilesID = findHostilesInEntities(world, enemy, hostile);
    if (!hostilesID.empty()) {
      allHostilesID.insert(allHostilesID.end(), hostilesID.begin(), hostilesID.end());
    }
  }
  return allHostilesID;
}

// Составление списка ID всех сущностей N-типа, которые пересекаются с зоной атаки конкретной враждебной сущности
std::vector<size_t> EnemiesLogicSystem::findHostilesInEntities(ecs::World& world, std::shared_ptr<ecs::Entity> enemy,
                                                               std::string hostileName) {
  auto entitiesList = world.getEntitiesInRange(0, 0);
  std::vector<size_t> hostilesID{};

  for (auto& entity : entitiesList) {
    if (entity->getEntityName() == hostileName) {
      auto hostileID = intersectionWithHostile(enemy, entity);
      if (hostileID) hostilesID.push_back(hostileID);
    }
  }
  return hostilesID;
}

// Пересекается ли конкретная сущность N-типа с зоной атаки конкретной враждебной сущности
size_t EnemiesLogicSystem::intersectionWithHostile(std::shared_ptr<ecs::Entity> enemy,
                                                   std::shared_ptr<ecs::Entity> hostile) {
  auto enemyLogicComp = enemy->getComponent<EnemyLogicComponent>();
  auto enemyLocationComp = enemy->getComponent<LocationComponent>();
  auto hostileLocationComp = hostile->getComponent<LocationComponent>();

  int xE{enemyLocationComp->column_}, yE{enemyLocationComp->row_}, xH{hostileLocationComp->column_},
      yH{hostileLocationComp->row_}, rE{static_cast<int>(enemyLogicComp->aggroRange_)};

  if (xH >= xE - rE && xH <= xE + rE && yH >= yE - rE && yH <= yE + rE) {
    return hostile->getID();
  } else {
    return 0;
  }
}

// Построение пути и последующее заполнение логического компонента врага командами по достижению необходимых координат
void EnemiesLogicSystem::buildingPathToTarget(std::shared_ptr<ecs::Entity> enemy, std::pair<int, int> targetLocation) {
  std::map<std::pair<int, int>, std::pair<size_t, bool>> points{};
  auto enemyLocationComp = enemy->getComponent<LocationComponent>();
  points[std::make_pair(enemyLocationComp->column_, enemyLocationComp->row_)] = std::make_pair(0, false);

  auto targetIt = points.begin();
  bool unreachable{};
  do {
    std::map<std::pair<int, int>, std::pair<size_t, bool>> pointsBuff(points);
    unreachable = true;

    for (auto point : pointsBuff) {
      if (!point.second.second) {
        pointCrossCheck(point.first, point.second.first, points);
      }
    }
    for (auto point : pointsBuff) {
      if (!point.second.second) {
        unreachable = false;
      }
    }
    targetIt = points.find(targetLocation);
    if (unreachable) break;
  } while (targetIt == points.end());

  auto enemyLogicComp = enemy->getComponent<EnemyLogicComponent>();
  if (!unreachable) {
    auto currentEnemyLocationIT = points.find(std::make_pair(enemyLocationComp->column_, enemyLocationComp->row_));
    points.erase(currentEnemyLocationIT);
    enemyLogicComp->steps_.push_back(targetLocation);
    targetIt = points.find(targetLocation);
    if (targetIt->second.first != 0) {
      auto targetCost = targetIt->second.first - 1;
      for (; targetCost > 0; --targetCost) {
        enemyLogicComp->steps_.push_back(takeNearAdjacentLocation(enemyLogicComp->steps_.back(), targetCost, points));
      }
    }
  } else {
    auto enemyLocComp = enemy->getComponent<LocationComponent>();
    enemyLogicComp->steps_.push_back(std::make_pair(enemyLocComp->column_, enemyLocComp->row_));
  }
}

// Проверка точки крестом
void EnemiesLogicSystem::pointCrossCheck(std::pair<int, int> pointLocation, size_t prevCost,
                                         std::map<std::pair<int, int>, std::pair<size_t, bool>>& points) {
  std::pair<int, int> left{pointLocation.first - 1, pointLocation.second};
  std::pair<int, int> right{pointLocation.first + 1, pointLocation.second};
  std::pair<int, int> top{pointLocation.first, pointLocation.second - 1};
  std::pair<int, int> bot{pointLocation.first, pointLocation.second + 1};

  pointCheck(left, prevCost, points);
  pointCheck(right, prevCost, points);
  pointCheck(top, prevCost, points);
  pointCheck(bot, prevCost, points);

  auto pointIt = points.find(pointLocation);
  pointIt->second.second = true;
}

void EnemiesLogicSystem::pointCheck(std::pair<int, int> pointLocation, size_t prevCost,
                                    std::map<std::pair<int, int>, std::pair<size_t, bool>>& points) {
  auto pointEntityIt = std::find(entitiesLocation_.begin(), entitiesLocation_.end(), pointLocation);
  if (pointEntityIt == entitiesLocation_.end()) {
    auto pointIt = points.find(pointLocation);
    if (pointIt == points.end()) {
      points[pointLocation] = std::make_pair(prevCost + 1, false);
    }
  }
}

std::pair<int, int> EnemiesLogicSystem::takeNearAdjacentLocation(
    std::pair<int, int> prevLocation, size_t prevCost, std::map<std::pair<int, int>, std::pair<size_t, bool>>& points) {
  std::vector<std::pair<int, int>> cross = {{prevLocation.first - 1, prevLocation.second},
                                            {prevLocation.first + 1, prevLocation.second},
                                            {prevLocation.first, prevLocation.second - 1},
                                            {prevLocation.first, prevLocation.second + 1}};

  for (auto crossPoint : cross) {
    auto point = points.find(crossPoint);
    if (point != points.end() && point->second.first == prevCost) {
      return point->first;
    }
  }
  return std::make_pair(0, 0);
}

void EnemiesLogicSystem::moveEnemy(std::shared_ptr<ecs::Entity> enemy) {
  auto enemyLogicComp = enemy->getComponent<EnemyLogicComponent>();
  auto enemyLocationComp = enemy->getComponent<LocationComponent>();
  auto enemyPrevLocationComp = enemy->getComponent<PreviousLocationComponent>();
  auto nextStep = enemyLogicComp->steps_.back();
  enemyLogicComp->steps_.pop_back();
  enemyPrevLocationComp->columnPrevious_ = enemyLocationComp->column_;
  enemyPrevLocationComp->rowPrevious_ = enemyLocationComp->row_;
  enemyLocationComp->column_ = nextStep.first;
  enemyLocationComp->row_ = nextStep.second;

  auto prevIt = std::find(entitiesLocation_.begin(), entitiesLocation_.end(),
                          std::make_pair(enemyPrevLocationComp->columnPrevious_, enemyPrevLocationComp->rowPrevious_));
  if (prevIt != entitiesLocation_.end()) {
    entitiesLocation_.erase(prevIt, prevIt + 1);
  }
  entitiesLocation_.push_back(std::make_pair(enemyLocationComp->column_, enemyLocationComp->row_));
}
