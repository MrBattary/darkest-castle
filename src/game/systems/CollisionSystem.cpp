//
// Created by Battary on 27.03.2020.
//

#include "game/systems/CollisionSystem.h"

CollisionSystem::CollisionSystem() {
  setID(500);
  addProcessedComponents(200);

  fillSubsystems();
}

std::shared_ptr<ICollision> CollisionSystem::findSubsystem(const std::string firstName, const std::string secondName) {
  std::string straightKey = firstName + secondName;
  std::string reverseKey = secondName + firstName;
  auto straightIt = collisionSubsystems_.find(straightKey);
  auto reverseIt = collisionSubsystems_.find(reverseKey);

  if (straightIt == collisionSubsystems_.end() && reverseIt == collisionSubsystems_.end()) {
    return nothing_;
  } else {
    if (straightIt == collisionSubsystems_.end()) {
      return collisionSubsystems_.at(reverseKey);
    }
    if (reverseIt == collisionSubsystems_.end()) {
      return collisionSubsystems_.at(straightKey);
    }
  }

  return nullptr;
}

// FirstName|SecondName = SecondName|FirstName
void CollisionSystem::fillSubsystems() {
  collisionSubsystems_["PlayerCoin"] = std::make_shared<CoinCollision>();
  collisionSubsystems_["PlayerWall"] = std::make_shared<WallCollision>();
  collisionSubsystems_["PlayerExit"] = std::make_shared<ExitCollision>();
  collisionSubsystems_["PlayerEnemy"] = std::make_shared<EnemyCollision>();
}

void CollisionSystem::separateEntities(std::vector<std::shared_ptr<ecs::Entity>>& allEntities,
                                       std::vector<std::shared_ptr<ecs::Entity>>& mEntities,
                                       std::vector<std::shared_ptr<ecs::Entity>>& nonmEntities) {
  for (auto it = allEntities.begin(); it != allEntities.end(); ++it) {
    if ((*it)->containComponent(201)) {
      mEntities.push_back(std::move(*it));
    } else {
      nonmEntities.push_back(std::move(*it));
    }
  }
  allEntities.clear();
}

bool CollisionSystem::confrontEntities(ecs::World& world, std::shared_ptr<ecs::Entity> fst,
                                       std::shared_ptr<ecs::Entity> snd) {
  auto firstLocation = fst->getComponent<LocationComponent>();
  auto secondLocation = snd->getComponent<LocationComponent>();

  if (firstLocation->column_ == secondLocation->column_ && firstLocation->row_ == secondLocation->row_) {
    auto subsystem = findSubsystem(fst->getEntityName(), snd->getEntityName());
    if (subsystem != nothing_) {
      subsystem->updateSubsystem(world, fst, snd);
      return false;
    } else {
      return true;
    }
  } else {
    return true;
  }
}

void CollisionSystem::updateSystem(ecs::World& world) {
  bool allEntitiesChecked{true};
  do {
    auto entities = world.getListEntities(getID());

    std::vector<std::shared_ptr<ecs::Entity>> movingEntities;
    std::vector<std::shared_ptr<ecs::Entity>> nonmovingEntities;

    separateEntities(entities, movingEntities, nonmovingEntities);

    for (auto it = movingEntities.begin(); it != movingEntities.end(); ++it) {
      allEntitiesChecked = true;
      auto jt = it == movingEntities.end() ? movingEntities.end() : (it + 1);
      for (; jt != movingEntities.end(); ++jt) {
        allEntitiesChecked = confrontEntities(world, *it, *jt);
        if (!allEntitiesChecked) break;
      }
      if (!allEntitiesChecked) break;
    }

    if (!allEntitiesChecked) continue;

    for (auto it = movingEntities.begin(); it != movingEntities.end(); ++it) {
      allEntitiesChecked = true;
      for (auto jt = nonmovingEntities.begin(); jt != nonmovingEntities.end(); ++jt) {
        allEntitiesChecked = confrontEntities(world, *it, *jt);
        if (!allEntitiesChecked) break;
      }
      if (!allEntitiesChecked) break;
    }
  } while (!allEntitiesChecked);
  return;
}
