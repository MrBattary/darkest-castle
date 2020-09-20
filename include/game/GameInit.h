//
// Created by Battary on 25.03.2020.
//

#pragma once

#include <memory>

#include "BearLibTerminal.h"
#include "game/lib/ECS/ECS.h"
// Entities
#include "entities/PlayerEntity.h"
#include "entities/ItemEntity.h"
#include "entities/WallEntity.h"
// Components
#include "components/SymbolComponent.h"
#include "components/LocationComponent.h"
#include "components/PreviousLocationComponent.h"
#include "components/DirectionComponent.h"
#include "components/ControlComponent.h"
#include "components/StatisticsComponent.h"
#include "components/StatsComponent.h"
#include "components/InventoryComponent.h"
// Systems
#include "systems/CoinGenerationSystem_deprecated.h"
#include "systems/CollisionSystem.h"
#include "systems/DebugSystem.h"
#include "systems/EnemiesLogicSystem.h"
#include "systems/EntitiesDisplaySystem.h"
#include "systems/InterfaceDisplaySystem.h"
#include "systems/InterfaceUpdateSystem.h"
#include "systems/InventoryStatsSystem.h"
#include "systems/KeyboardInputSystem.h"
#include "systems/MapFormationSystem.h"
#include "systems/PlayerMovementSystem.h"

//Initialization
std::unique_ptr<ecs::World> GameInit();
