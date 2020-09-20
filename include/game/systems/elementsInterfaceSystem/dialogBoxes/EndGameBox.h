//
// Created by Battary on 04.08.2020.
//

#pragma once
// Internal templates
#include "../IDialogBoxElement.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/PlayerRealtimeStatisticsBox.h"
#include "game/systems/elementsInterfaceSystem/messageBoxes/LeaderboardBox.h"
// Entities
#include "game/entities/PlayerEntity.h"
#include "game/entities/ItemEntity.h"
#include "game/entities/WallEntity.h"
// Components
#include "game/components/SymbolComponent.h"
#include "game/components/LocationComponent.h"
#include "game/components/PreviousLocationComponent.h"
#include "game/components/DirectionComponent.h"
#include "game/components/ControlComponent.h"
#include "game/components/StatisticsComponent.h"
#include "game/components/StatsComponent.h"
#include "game/components/InventoryComponent.h"
// Systems
#include "game/systems/CoinGenerationSystem_deprecated.h"
#include "game/systems/CollisionSystem.h"
#include "game/systems/DebugSystem.h"
#include "game/systems/EnemiesLogicSystem.h"
#include "game/systems/EntitiesDisplaySystem.h"
#include "game/systems/InterfaceDisplaySystem.h"
#include "game/systems/InterfaceUpdateSystem.h"
#include "game/systems/InventoryStatsSystem.h"
#include "game/systems/KeyboardInputSystem.h"
#include "game/systems/MapFormationSystem.h"
#include "game/systems/PlayerMovementSystem.h"

// Окно при завершении игры
class EndGameBox : public IDialogBoxElement {
 public:
  explicit EndGameBox(ecs::World&);

  void updateElement(ecs::World&) override;

  ~EndGameBox() override = default;
};
