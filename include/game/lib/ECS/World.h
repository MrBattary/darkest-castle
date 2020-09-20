//
// Created by Battary on 27.04.2020.
//

#pragma once

#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Entity.h"
#include "System.h"

namespace ecs {
class World {
 private:
  std::map<size_t, std::shared_ptr<ecs::System>> systems_{};
  std::map<size_t, std::shared_ptr<ecs::Entity>> entities_{};
  std::map<size_t, std::vector<std::shared_ptr<ecs::Entity>>> pairSysIDEntID_{};
  size_t lastEntityID_{0};
  bool activeCleaning_{false};
  bool terminateApplicationStatus_{false};

 public:
  World(const World&) = delete;
  World& operator=(const World&) = delete;

  explicit World(bool activeCleaning = false) : activeCleaning_(activeCleaning) {}

  //Получить последний ID, который использует сущность
  size_t getLastEntityID() {
    return lastEntityID_;
  }

  void resetLastEntityID() {
    lastEntityID_ = 0;
  }

  //Добавить сущность в мир, используя уже существующий экземпляр сущности
  template<typename TEntity>
  size_t addEntity(std::shared_ptr<TEntity> addingEntity) {
    if (addingEntity->getID() == (size_t) 0) {
      addingEntity->setID(++lastEntityID_);
    } else {
      lastEntityID_ = addingEntity->getID();
    }

    // entities_.insert(std::make_pair<size_t, std::shared_ptr<TEntity>>(addingEntity->getID(),
    // std::move(addingEntity)));
    size_t id = addingEntity->getID();
    entities_[id] = std::move(addingEntity);
    return id;
  }

  //Добавить сущность в мир
  template<typename TEntity>
  void createEntity() {
    std::shared_ptr<TEntity> buff(new TEntity);
    buff->setID(++lastEntityID_);
    entities_.insert(std::make_pair(buff->getID(), buff));
  }

  //Добавить сущность в мир и вернуть её id
  template<typename TEntity>
  size_t createEntityAndReturnID() {
    std::shared_ptr<TEntity> buff(new TEntity);
    buff->setID(++lastEntityID_);
    size_t returnID = buff->getID();
    entities_.insert(std::make_pair(buff->getID(), buff));
    return returnID;
  }

  //Удалить сущность по ID из мира
  void purgeEntity(size_t purgingEntityID) {
    size_t keyOfPurgingEntity(0);
    for (auto& entity : entities_) {
      if (entity.second->getID() == purgingEntityID) {
        keyOfPurgingEntity = entity.first;
        entities_.erase(keyOfPurgingEntity);
        break;
      }
    }
  }

  //Проверить наличие сущности
  bool containEntity(size_t containingEntityID) const {
    return entities_.count(containingEntityID) != 0;
  }

  //Посчитать количество сущностей с одинаковым названием
  size_t countEntity(std::string entityName) const {
    size_t count{0};
    for (const auto& entities : entities_) {
      if (!entities.second->getEntityName().compare(entityName)) {
        count++;
      }
    }
    return count;
  }

  //Получить ссылку на сущность по ID
  template<typename TEntity>
  std::shared_ptr<TEntity> getEntity(size_t entityID) const {
    for (const auto& entities : entities_) {
      if (entities.second->getID() == entityID) {
        auto pointer = entities_.at(entityID);
        return std::dynamic_pointer_cast<TEntity>(pointer);
      }
    }
    return nullptr;
  }

  //Получить ссылку на сущность без ID, работает только, если сущность в единственном экземпляре
  template<typename TEntity>
  std::shared_ptr<TEntity> getEntity() const {
    std::unique_ptr<TEntity> buff(new TEntity());
    auto entityNumber = countEntity(buff->getEntityName());
    if (entityNumber == 1) {
      for (const auto& entities : entities_) {
        if (entities.second->getID() == buff->getID()) {
          auto pointer = entities_.at(buff->getID());
          return std::dynamic_pointer_cast<TEntity>(pointer);
        }
      }
    }
    return nullptr;
  }

  //Получить ссылки на сущности в промежутке от entities_.begin()+begin до entities_.end()-end
  std::vector<std::shared_ptr<ecs::Entity>> getEntitiesInRange(size_t begin, size_t end) const {
    std::vector<std::shared_ptr<ecs::Entity>> buff{};
    if (entities_.size() > begin && entities_.size() > end && entities_.size() - end > begin) {
      for (auto it = std::next(entities_.begin(), begin); it != std::prev(entities_.end(), end); ++it) {
        buff.push_back(it->second);
      }
    }
    return buff;
  }

  //Удалить все сущности из мира
  void clearEntities() {
    entities_.clear();
  }

  //Удалить сущности от начала+begin до конца-end
  void purgeEntities(size_t begin, size_t end) {
    if (entities_.size() - end >= begin && begin <= entities_.size()) {
      auto bt = entities_.begin();
      auto et = entities_.end();
      std::advance(bt, begin);
      std::advance(et, -end);
      entities_.erase(bt, et);
    }
  }

  //Добавить систему в мир
  template<typename TSystem>
  void addSystem(std::shared_ptr<TSystem> addingSystem) {
    systems_.insert(std::make_pair(addingSystem->getID(), std::move(addingSystem)));
  }

  //Создать систему в мире
  template<typename TSystem>
  void createSystem() {
    std::shared_ptr<TSystem> buff(new TSystem);
    systems_.insert(std::make_pair(buff->getID(), std::move(buff)));
  }

  //Создать систему в мире со списком аргументов
  template<typename TSystem, typename... Args>
  void createSystem(Args&&... args) {
    std::shared_ptr<TSystem> buff(new TSystem(std::forward<Args>(args)...));
    const size_t id = buff->getID();
    systems_[id] = std::move(buff);
  }

  //Получить ссылку на систему
  template<typename TSystem>
  std::shared_ptr<TSystem> getSystem() const {
    // std::unique_ptr<TSystem> buff(new TSystem());
    auto buff = std::make_unique<TSystem>();
    const size_t systemID = buff->getID();
    for (const auto& systems : systems_) {
      if (systems.second->getID() == systemID) {
        auto pointer = systems_.at(systemID);
        return std::dynamic_pointer_cast<TSystem>(pointer);
      }
    }
    return nullptr;
  }

  //Получить ссылку на систему по ID
  template<typename TSystem>
  std::shared_ptr<TSystem> getSystem(size_t systemID) const {
    for (const auto& systems : systems_) {
      if (systems.second->getID() == systemID) {
        auto pointer = systems_.at(systemID);
        return std::dynamic_pointer_cast<TSystem>(pointer);
      }
    }
    return nullptr;
  }

  //Удалить систему из мира по ID
  void purgeSystem(size_t purgingSystemID) {
    systems_.erase(purgingSystemID);
  }

  //Удалить систему из мира по её типу
  template<typename TSystem>
  void purgeSystem() {
    std::unique_ptr<TSystem> buff(new TSystem());
    const size_t id = buff->getID();
    systems_.erase(id);
  }

  //Синхронизировать сущности и системы
  //Необходимо вызывать каждый раз, при любом изменении сущностей/компонентов/систем
  // TODO(Battary): Оптимизировать, чтобы не пересобирать весь список заново
  void updateWorldList() {
    pairSysIDEntID_.clear();

    for (auto& system : systems_) {
      std::vector<size_t> componentsInsideSystem = system.second->getProcessedComponentsID();

      auto searchForSystem = pairSysIDEntID_.find(system.first);

      if (searchForSystem == pairSysIDEntID_.end()) {
        pairSysIDEntID_[system.first] = std::vector<std::shared_ptr<ecs::Entity>>{};
      }

      for (auto& entity : entities_) {
        bool containsAll = true;

        for (auto component : componentsInsideSystem) {
          if (!entity.second->containComponent(component)) {
            containsAll = false;
            break;
          }
        }

        if (containsAll) {
          pairSysIDEntID_[system.first].push_back(entity.second);
        }
      }
    }
  }

  //Получить сслыку на список сущностей для системы
  std::vector<std::shared_ptr<ecs::Entity>> getListEntities(size_t sysID) const {
    if (pairSysIDEntID_.find(sysID) != pairSysIDEntID_.end()) {
      return pairSysIDEntID_.at(sysID);
    } else {
      return std::vector<std::shared_ptr<ecs::Entity>>{};
    }
  }

  //Обновить мир
  void refreshWorld() {
    if (activeCleaning_) {
      for (auto& it : systems_) {
        if (!(systems_.at(it.first)->getInactive())) {
          systems_.at(it.first)->updateSystem(*this);
        }
      }
    } else {
      for (auto& it : systems_) {
        systems_.at(it.first)->updateSystem(*this);
      }
    }
  }

  void terminateApplication() {
    terminateApplicationStatus_ = true;
  }

  bool getTerminateApplicationStatus() const {
    return terminateApplicationStatus_;
  }

  //Очистить мир
  void clearWorld() {
    entities_.clear();
    systems_.clear();
    pairSysIDEntID_.clear();
  }

  ~World() {
    clearWorld();
  }
};
}  // namespace ecs
