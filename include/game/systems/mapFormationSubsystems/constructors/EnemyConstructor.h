//
// Created by Battary on 30.07.2020.
//

#pragma once
#include <map>
#include <memory>
#include <string>

#include "IConstructor.h"
// Entity
#include "game/entities/EnemyEntity.h"
// Components
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
// Internal constructors
#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/IEnemy.h"
#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/RedEnemy.h"
#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/BlueEnemy.h"
#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/SilverEnemy.h"
#include "game/systems/mapFormationSubsystems/constructors/enemiesTypes/NothingEnemy.h"

//Конструктор создающий врагов
class EnemyConstructor : public IConstructor {
 private:
  std::map<std::string, std::shared_ptr<IEnemy>> enemies_;
  std::shared_ptr<NothingEnemy> nothing_ = std::make_shared<NothingEnemy>();

  std::shared_ptr<IEnemy> findConstructor(std::string);
  void fillConstructors();
 public:
  EnemyConstructor();

  void constructObject(ecs::World&, std::string) override;

  ~EnemyConstructor() override = default;
};
