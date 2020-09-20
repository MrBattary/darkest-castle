//
// Created by Battary on 30.07.2020.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "game/lib/ECS/ECS.h"
#include "game/lib/Random/Random.h"

// Entities
#include "game/entities/EnemyEntity.h"
#include "game/entities/PlayerEntity.h"
// Components
#include "game/components/DirectionComponent.h"
#include "game/components/EnemyLogicComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"

// Система контролирующая ИИ врагов
class EnemiesLogicSystem : public ecs::System {
 private:
  std::vector<std::pair<int, int>> entitiesLocation_;

  void fillEntitiesLocation(ecs::World&);
  std::vector<std::pair<int, int>> cutEnemies(ecs::World&, std::shared_ptr<ecs::Entity>);
  size_t targetSelection(ecs::World&, std::shared_ptr<ecs::Entity>);
  std::vector<size_t> findHostilesInEntities(ecs::World&, std::shared_ptr<ecs::Entity>, std::string);
  std::vector<size_t> confrontationWithHostiles(ecs::World&, std::shared_ptr<ecs::Entity>);
  size_t intersectionWithHostile(std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);
  void buildingPathToTarget(std::shared_ptr<ecs::Entity>, std::pair<int, int>);
  void pointCrossCheck(std::pair<int, int>, size_t, std::map<std::pair<int, int>, std::pair<size_t, bool>>&);
  void pointCheck(std::pair<int, int>, size_t, std::map<std::pair<int, int>, std::pair<size_t, bool>>&);
  std::pair<int, int> takeNearAdjacentLocation(std::pair<int, int>, size_t,
                                               std::map<std::pair<int, int>, std::pair<size_t, bool>>&);
  void moveEnemy(std::shared_ptr<ecs::Entity>);

 public:
  EnemiesLogicSystem();

  void updateSystem(ecs::World&) override;

  ~EnemiesLogicSystem() override = default;
};
