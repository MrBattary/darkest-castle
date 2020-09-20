//
// Created by Battary on 29.07.2020.
//

#include "game/systems/elementsInterfaceSystem/messageBoxes/LeaderboardBox.h"
LeaderboardBox::LeaderboardBox() {
  setVariables(60, 8, "");
  name_ = "Leaderboard";
  expendable_ = false;
  reqUpdNumbers_ = {1};
}

void LeaderboardBox::updateElement(ecs::World& world) {
  if (elementData_.empty()) {
    std::ifstream boardStreamIN;
    if (!openStream(boardStreamIN)) {
      char buff{};
      std::string note{};
      while (boardStreamIN.read(&buff, sizeof(char))) {
        std::string buffNote(1, buff);

        if (buffNote != "*") {
          note += buffNote;
        } else {
          auto namePos = note.find("@");
          auto scorePos = note.find("$");
          auto stepsPos = note.find(">");
          std::string name = note.substr(namePos + 1, scorePos - namePos - 1);
          auto score = std::stoul(note.substr(scorePos + 1, stepsPos - scorePos - 1));
          auto steps = std::stoul(note.substr(stepsPos + 1));
          leaderboard_.insert(std::make_pair(score, std::make_pair(steps, name)));
          note.clear();
        }
      }
      boardStreamIN.close();
      auto playerEnt = world.getEntity<Player>();
      auto statisticsComp = playerEnt->getComponent<StatisticsComponent>();
      leaderboard_.insert(
          std::make_pair(statisticsComp->coins_, std::make_pair(statisticsComp->steps_, playerEnt->getEntityName())));

      std::ofstream boardStreamOUT;
      if (!openStream(boardStreamOUT)) {
        auto itend = leaderboard_.rbegin();
        if (leaderboard_.size() > 5) {
          std::advance(itend, 5);
        } else {
          itend = leaderboard_.rend();
        }
        for (auto it = leaderboard_.rbegin(); it != itend; ++it) {
          boardStreamOUT << "@" + it->second.second + "$" + std::to_string(it->first) + ">" +
                                std::to_string(it->second.first) + "*";
        }
        boardStreamOUT.close();

        for (auto it = leaderboard_.rbegin(); it != itend; ++it) {
          elementData_ += it->second.second + "  $: " + std::to_string(it->first) + "\n";
          for (auto i = it->second.second.size() + 2; i > 0; i--) {
            elementData_ += " ";
          }
          elementData_ += "S: " + std::to_string(it->second.first) + "\n";
        }
      }
    } else {
      elementData_ = "ERROR";
    }
  }
}

int LeaderboardBox::openStream(std::ifstream& stream) {
  std::string filenameWindows = "..\\data\\board.leaderboard";
  std::string filenameLinux = "../data/board.leaderboard";
  std::string filenameCMake = "data/board.leaderboard";

  stream.open(filenameWindows, std::ios::binary | std::ios::in);
  if (!stream.is_open()) {
    stream.clear();
    stream.open(filenameLinux, std::ios::binary | std::ios::in);
    if (!stream.is_open()) {
      stream.clear();
      stream.open(filenameCMake, std::ios::binary | std::ios::in);
      if (!stream.is_open()) {
        return 1;
      }
    }
  }
  return 0;
}

int LeaderboardBox::openStream(std::ofstream& stream) {
  std::string filenameWindows = "..\\data\\board.leaderboard";
  std::string filenameLinux = "../data/board.leaderboard";
  std::string filenameCMake = "data/board.leaderboard";

  stream.open(filenameWindows, std::ios::binary | std::ios::out);
  if (!stream.is_open()) {
    stream.clear();
    stream.open(filenameLinux, std::ios::binary | std::ios::out);
    if (!stream.is_open()) {
      stream.clear();
      stream.open(filenameCMake, std::ios::binary | std::ios::out);
      if (!stream.is_open()) {
        return 1;
      }
    }
  }
  return 0;
}
