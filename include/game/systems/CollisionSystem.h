//
// Created by Battary on 27.03.2020.
//

#pragma once

#include <map>
#include <vector>
#include <memory>
#include <string>

#include "game/lib/ECS/ECS.h"
// Components
#include "game/components/LocationComponent.h"
// Collision types
#include "collisionSubsystems/CoinCollision.h"
#include "collisionSubsystems/ExitCollision.h"
#include "collisionSubsystems/NothingCollision.h"
#include "collisionSubsystems/WallCollision.h"
#include "collisionSubsystems/EnemyCollision.h"

//Система коллизий между объектами, проверяет факт столкновения, обработку дилегирует подсистемам
class CollisionSystem : public ecs::System {
 private:
  std::map<std::string, std::shared_ptr<ICollision>> collisionSubsystems_{};
  std::shared_ptr<NothingCollision> nothing_ = std::make_shared<NothingCollision>();

  void fillSubsystems();
  std::shared_ptr<ICollision> findSubsystem(const std::string, const std::string);

  void separateEntities(std::vector<std::shared_ptr<ecs::Entity>> &, std::vector<std::shared_ptr<ecs::Entity>> &,
                        std::vector<std::shared_ptr<ecs::Entity>> &);
  bool confrontEntities(ecs::World &, std::shared_ptr<ecs::Entity>, std::shared_ptr<ecs::Entity>);

 public:
  CollisionSystem();

  void updateSystem(ecs::World&) override;

  ~CollisionSystem() override = default;
};
