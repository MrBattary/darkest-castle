//
// Created by Battary on 27.04.2020.
//

#pragma once

#include <iostream>
#include <set>
#include <vector>

namespace ecs {
class World;

//Система-шаблон
class System {
 private:
  std::set<size_t> processedComponents_{};
  size_t idSystem_{0};  //Уникальный ID системы, чем больше ID тем ниже приоритет обработки системы
  bool inactive_{false};  //Если true, то мир проигнорирует систему при обработке

 public:
  //Задать уникальный ID системы
  void setID(size_t value) {
    idSystem_ = value;
  }

  //Получить уникальный ID системы
  size_t getID() const {
    return idSystem_;
  }

  //Узнать состояние системы
  bool getInactive() {
    return inactive_;
  }

  //Установить состояние системы
  void setInactive(bool type) {
    inactive_ = type;
  }

  //Добавить ID(size_t) компонента, который обрабатывает система
  template<typename T>
  void addProcessedComponents(const T& addingComponentID) {
    processedComponents_.insert(addingComponentID);
  }

  //Добавить ID(size_t) компонентов, которые обрабатывает система
  template<typename First, typename... Rest>
  void addProcessedComponents(const First& first, const Rest&... rest) {
    processedComponents_.insert(first);
    addProcessedComponents(rest...);
  }

  //Удалить обрабатываемый компонент по ID
  void removeProcessedComponent(size_t removingComponentID) {
    processedComponents_.erase(removingComponentID);
  }

  //Узнать по ID компонента, обрабатывает ли такие компоненты эта система
  bool containProcessedComponent(size_t componentID) const {
    return processedComponents_.count(componentID) != 0;
  }

  //Получить массив компонентов, которые обрабатывает данная система
  std::vector<size_t> getProcessedComponentsID() const {
    std::vector<size_t> resultVector(processedComponents_.begin(), processedComponents_.end());
    return resultVector;
  }

  virtual ~System() {
    processedComponents_.clear();
  }

  //Обновить систему
  virtual void updateSystem(ecs::World&) {}
};
}  // namespace ecs
