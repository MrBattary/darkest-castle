//
// Created by Battary on 28.04.2020.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "game/lib/ECS/ECS.h"

// Методы формирования карты
#include "mapFormationSubsystems/GenerateMap.h"
#include "mapFormationSubsystems/ReceiveMap.h"

// Constructors
#include "mapFormationSubsystems/constructors/CoinConstructor.h"
#include "mapFormationSubsystems/constructors/ExitConstructor.h"
#include "mapFormationSubsystems/constructors/IConstructor.h"
#include "mapFormationSubsystems/constructors/NothingConstructor.h"
#include "mapFormationSubsystems/constructors/WallConstructor.h"
#include "mapFormationSubsystems/constructors/EnemyConstructor.h"
#include "mapFormationSubsystems/constructors/enemiesTypes/RedEnemy.h"

// Система которая отвечает за формирование карты
class MapFormationSystem : public ecs::System {
 private:
  int nextMapNumber_, currentMapNumber_{0};
  bool firstMapFormed_{false};

  std::map<std::string, std::shared_ptr<IConstructor>> constructors_{};
  std::shared_ptr<NothingConstructor> nothing_ = std::make_shared<NothingConstructor>();
  std::map<int, std::vector<std::shared_ptr<ecs::Entity>>> mapsStorage_{};
  std::vector<std::string> objects_{};

  std::shared_ptr<IConstructor> findConstructor(std::string);
  void mapUpdateOrLoad(ecs::World&);
  void fillConstructors();

 public:
  explicit MapFormationSystem(int);

  void updateSystem(ecs::World&) override;

  void setNextMap(int);

  ~MapFormationSystem() override = default;
};
