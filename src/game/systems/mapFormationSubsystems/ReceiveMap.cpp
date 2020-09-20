//
// Created by Battary on 25.05.2020.
//

#include "game/systems/mapFormationSubsystems/ReceiveMap.h"

ReceiveMap::ReceiveMap(size_t map = 0) : mapNumber_(map) {}

/*bool ReceiveMap::checkMapHash(std::string filepath) {

  CryptoPP::SHA3_256 hash;
  CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

  std::ifstream mapStream;
  mapStream.open(filepath, std::ios::binary | std::ios::in);

  std::string text {};
  char buff {};
  while (mapStream.read(&buff, sizeof(char))) {
    std::string buffSymb(1, buff);
    text += buffSymb;
  }

  std::string resultHash;

  hash.Update((const CryptoPP::byte*)text.data(), text.size());
  resultHash.resize(hash.DigestSize());
  hash.Final((CryptoPP::byte*) & resultHash[0]);

  return resultHash == hashs_.at(mapNumber_);
}*/

int ReceiveMap::openStream(std::ifstream& stream) {
  std::string mapFilenameWindows = "..\\data\\levels\\" + std::to_string(mapNumber_) + ".txt";
  std::string mapFilenameLinux = "../data/levels/" + std::to_string(mapNumber_) + ".txt";
  std::string mapFilepathCMake = "data/levels/" + std::to_string(mapNumber_) + ".txt";

  stream.open(mapFilenameWindows, std::ios::in);
  if (!stream.is_open()) {
    stream.clear();
    stream.open(mapFilenameLinux, std::ios::in);
    if (!stream.is_open()) {
      stream.clear();
      stream.open(mapFilepathCMake, std::ios::in);
      if (!stream.is_open()) {
        return 1;
      } else {
        /*if(!checkMapHash(mapFilepathCMake)){
          stream.close();
        }*/
      }
    } else {
      /*if(!checkMapHash(mapFilenameLinux)){
        stream.close();
      }*/
    }
  } else {
    /*if(!checkMapHash(mapFilenameWindows)){
      stream.close();
    }*/
  }
  return 0;
}

int ReceiveMap::readMap() {
  std::ifstream mapStream;

  if (!openStream(mapStream)) {
    char buff;
    int x{0}, y{0};
    std::string objectFromFile;

    while (mapStream.read(&buff, sizeof(char))) {
      std::string buffObj(1, buff);

      if (buffObj != "\n") {
        if (buffObj == " ") {
          std::string xStr, yStr;
          if (x < 10) {
            xStr = "0" + std::to_string(x);
          } else {
            xStr = std::to_string(x);
          }
          if (y < 10) {
            yStr = "0" + std::to_string(y);
          } else {
            yStr = std::to_string(y);
          }
          objectFromFile += "AxisX" + xStr + "AxisY" + yStr;

          objectsFromFile_.push_back(objectFromFile);
          objectFromFile.clear();

          x++;
        } else {
          objectFromFile += buffObj;
        }
      } else {
        y++;
        x = 0;
      }
    }
    mapStream.close();

    return 0;
  } else {
    return 1;
  }
}

std::vector<std::string> ReceiveMap::BuildMap(ecs::World& world) {
  if (!readMap()) {
    return objectsFromFile_;
  } else {
    return std::vector<std::string>{};
  }
}
