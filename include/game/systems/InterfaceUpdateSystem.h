//
// Created by Battary on 28.05.2020.
//

#pragma once

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"
// Templates
#include "elementsInterfaceSystem/IDialogBoxElement.h"
#include "elementsInterfaceSystem/IElement.h"
#include "elementsInterfaceSystem/IMessageBoxElement.h"
// Boxes
#include "elementsInterfaceSystem/dialogBoxes/EndLevelBox.h"
#include "elementsInterfaceSystem/dialogBoxes/MenuBox.h"
#include "elementsInterfaceSystem/dialogBoxes/HelpBox.h"
#include "elementsInterfaceSystem/dialogBoxes/InventoryBox.h"
#include "elementsInterfaceSystem/messageBoxes/MenuMiniBox.h"
#include "elementsInterfaceSystem/messageBoxes/InventoryMiniBox.h"
#include "elementsInterfaceSystem/messageBoxes/HelpMiniBox.h"
#include "elementsInterfaceSystem/messageBoxes/PlayerRealtimeLogBox.h"
#include "elementsInterfaceSystem/messageBoxes/PlayerRealtimeStatisticsBox.h"
#include "elementsInterfaceSystem/messageBoxes/PlayerHealthBox.h"

class InterfaceDisplaySystem;

// Класс отвечает за обновление элементов интерфейса
class InterfaceUpdateSystem : public ecs::System {
 private:
  std::map<std::string, std::shared_ptr<IElement>> elements_{};
  std::string command_{};
  bool blockNewWindows_ {false};

  void freezeEntities(ecs::World &);
  void addElements(ecs::World &);

 public:
  InterfaceUpdateSystem();

  friend class InterfaceDisplaySystem;

  void updateSystem(ecs::World&) override;

  void deleteElement(std::string);


  template<typename TElement, typename... Args>
  void createElement(Args &&... args) {
    std::shared_ptr<TElement> buff(new TElement(std::forward<Args>(args)...));
    const std::string name = buff->getName();
    elements_[name] = std::move(buff);
  }

  template<typename TElement>
  std::shared_ptr<TElement> getElement() const {
    auto buffElem = std::make_unique<TElement>();
    const std::string buffElemName = buffElem->getName();

    for (const auto& element : elements_) {
      if (element.first == buffElemName) {
        auto pointer = elements_.at(buffElemName);
        return std::dynamic_pointer_cast<TElement>(pointer);
      }
    }
    return nullptr;
  }

  bool containElement(std::string) const;

  bool getElementExpendableStatus(std::string) const;

  void setCommand(std::string);
  std::string getCommand() const;

  void blockNewWindows();
  void unblockNewWindows();

  void hideAllExcept(std::initializer_list<std::string>);

  void unhideAllExcept(std::initializer_list<std::string>);

  ~InterfaceUpdateSystem() override = default;
};
