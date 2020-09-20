//
// Created by Battary on 28.04.2020.
//

#include "game/systems/MapFormationSystem.h"

MapFormationSystem::MapFormationSystem(int map = 0) : nextMapNumber_(map) {
  setID(100);
  addProcessedComponents(0);
  fillConstructors();
}

void MapFormationSystem::fillConstructors() {
  constructors_["$"] = std::make_shared<CoinConstructor>();
  constructors_["#"] = std::make_shared<WallConstructor>();
  constructors_[">"] = std::make_shared<ExitConstructor>();
  constructors_["<"] = std::make_shared<ExitConstructor>();
  constructors_["E"] = std::make_shared<EnemyConstructor>();
}

std::shared_ptr<IConstructor> MapFormationSystem::findConstructor(std::string objectType) {
  auto constructorPointer = constructors_.find(objectType);

  if (constructorPointer == constructors_.end()) {
    return nothing_;
  } else {
    return constructors_.at(objectType);
  }
}

void MapFormationSystem::mapUpdateOrLoad(ecs::World& world) {
  if (firstMapFormed_) {
    auto map = mapsStorage_.find(nextMapNumber_);
    if (map != mapsStorage_.end()) {
      mapsStorage_.erase(currentMapNumber_);
    }
    mapsStorage_[currentMapNumber_] = world.getEntitiesInRange(1, 0);
  } else {
    firstMapFormed_ = true;
  }
}

void MapFormationSystem::updateSystem(ecs::World& world) {
  mapUpdateOrLoad(world);

  world.purgeEntities(1, 0);

  auto map = mapsStorage_.find(nextMapNumber_);
  if (map == mapsStorage_.end()) {
    if (nextMapNumber_ >= 0) {
      std::unique_ptr<ReceiveMap> receiver(new ReceiveMap(nextMapNumber_));
      objects_ = receiver->BuildMap(world);
    }
    if (nextMapNumber_ < 0 || objects_.empty()) {
      std::unique_ptr<GenerateMap> generator(new GenerateMap(nextMapNumber_));
      objects_ = generator->BuildMap(world);
    }
    for (auto& it : objects_) {
      std::string objectType = it.substr(0, 1);
      auto constructor = findConstructor(objectType);
      constructor->constructObject(world, it);
    }
  } else {
    for (auto it = map->second.begin(); it != map->second.end(); ++it) {
      world.addEntity(*it);
    }
  }
  currentMapNumber_ = nextMapNumber_;
  world.updateWorldList();
  setInactive(true);
}

void MapFormationSystem::setNextMap(int mapNumber) {
  nextMapNumber_ = mapNumber;
}
