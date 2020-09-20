//
// Created by Battary on 30.07.2020.
//

#include "game/systems/mapFormationSubsystems/constructors/EnemyConstructor.h"

EnemyConstructor::EnemyConstructor() {
  fillConstructors();
}

void EnemyConstructor::fillConstructors() {
  enemies_["Red"] = std::make_shared<RedEnemy>();
  enemies_["Blu"] = std::make_shared<BlueEnemy>();
  enemies_["Sil"] = std::make_shared<SilverEnemy>();
}

std::shared_ptr<IEnemy> EnemyConstructor::findConstructor(std::string enemyType) {
  auto constructorPointer = enemies_.find(enemyType);

  if (constructorPointer == enemies_.end()) {
    return nothing_;
  } else {
    return enemies_.at(enemyType);
  }
}

void EnemyConstructor::constructObject(ecs::World& world, std::string obj) {
  size_t enemyID = world.createEntityAndReturnID<Enemy>();
  auto enemy = world.getEntity<Enemy>(enemyID);
  enemy->setEntityName("Enemy");

  std::string enemyType = obj.substr(1, 3);
  auto enemyConstructor = findConstructor(enemyType);
  enemyConstructor->createEnemy(enemy);

  int x{0}, y{0};
  std::tie(x, y) = pullCoords(obj);
  enemy->addComponent<LocationComponent>(x, y);
  enemy->addComponent<PreviousLocationComponent>();
}
