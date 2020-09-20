//
// Created by Battary on 25.03.2020.
//

#pragma once

#include <memory>

#include "BearLibTerminal.h"
#include "GameInit.h"
#include "game/lib/ECS/ECS.h"

//Main game loop
void GameLoop(std::unique_ptr<ecs::World> world);
