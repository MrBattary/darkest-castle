//
// Created by Battary on 25.05.2020.
//

#pragma once

#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>
/*#include "sha3.h"
#include "files.h"
#include "filters.h"
#include "hex.h"*/
#include "game/lib/ECS/ECS.h"
#include "IMap.h"

// Класс отвечает за чтение карты из файла
class ReceiveMap : public IMap {
 private:
  size_t mapNumber_;
  std::vector<std::string> objectsFromFile_{};
  const std::map<size_t, std::string> hashs_{{0, "CF99DA7BCBC44504A5591F6346DAFC784F1BF877A9E0C35CEA80AFE58501DF04"},
                                             {1, "262FA36BE00DC28A81A772296E99CEEBC935D618B897CE0A41363BD4F9D9A8ED"},
                                             {2, "7E0DC2E9199C74F36D5E9899E716B6CF7918D5847A44971CE858330A5F58C2AA"}};

  // bool checkMapHash(std::string);
  int openStream(std::ifstream &);
  int readMap();

 public:
  explicit ReceiveMap(size_t);

  std::vector<std::string> BuildMap(ecs::World &) override;

  ~ReceiveMap() override = default;
};
