//
// Created by Battary on 27.04.2020.
//

#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <utility>
#include <vector>

#include "Component.h"

namespace ecs {
//Сущность-шаблон
class Entity {
 private:
  std::map<size_t, std::shared_ptr<ecs::Component>> components_{};
  std::string entityName_{};
  size_t idEntity_{0};

 public:
  // TODO(Battary): Добавить activate/deactivate

  //Задать имя сущности
  void setEntityName(const std::string entityName) {
    entityName_ = entityName;
  }

  //Получить имя сущности
  const std::string getEntityName() {
    return entityName_;
  }

  //Задать уникальный ID сущности
  void setID(const size_t id) {
    idEntity_ = id;
  }

  //Получить уникальный ID сущности
  size_t getID() const {
    return idEntity_;
  }

  //Узнать по ID компонента, есть ли такие компоненты в данной сущности
  bool containComponent(size_t componentID) const {
    return components_.count(componentID) != 0;
  }

  //Получить массив всех компонентов в сущности
  std::vector<size_t> getContainsComponentsID() const {
    std::vector<size_t> resultVector;
    std::transform(components_.cbegin(), components_.cend(), std::back_inserter(resultVector),
                   [](auto&& arg) { return arg.first; });
    return resultVector;
  }

  //Получить ссылку на компонент
  template<typename TComponent>
  std::shared_ptr<TComponent> getComponent() const {
    std::unique_ptr<TComponent> buff(new TComponent);
    const size_t componentID = buff->getComponentID();

    for (const auto& component : components_) {
      if (component.second->getComponentID() == componentID) {
        auto pointer = components_.at(componentID);
        return std::dynamic_pointer_cast<TComponent>(pointer);
      }
    }
    return nullptr;
  }

  //Добавить уже существующий компонент
  template<typename TComponent>
  void addComponent(std::shared_ptr<TComponent> addingComponent) {
    components_[addingComponent->getComponentID()] = std::move(addingComponent);
  }

  //Добавить компонент с помощью конструктора
  template<typename TComponent, typename... Args>
  void addComponent(Args&&... args) {
    auto buff = std::make_shared<TComponent>(std::forward<Args>(args)...);
    const size_t id = buff->getComponentID();
    components_[id] = std::move(buff);
  }

  //Добавить несколько компонентов
  template<typename... Args>
  void addComponents() {
    const auto unused = {true, (addComponent<Args>(), void(), true)...};
    (void) unused;
  }

  //Удалить компонент по ID
  void removeComponent(size_t removingID) {
    components_.erase(removingID);
  }

  //Удалить компонент по типу
  template<typename TComponent>
  void removeComponent() {
    auto buff = std::make_unique<TComponent>();
    const size_t id = buff->getComponentID();
    components_.erase(id);
  }

  //Узнать количество компонентов в сущности
  size_t howManyComponents() const {
    return components_.size();
  }

  //Удалить все компоненты из сущности
  void removeAllComponents() {
    components_.clear();
  }

  virtual ~Entity() {
    removeAllComponents();
  }
};
}  // namespace ecs
