# Darkest Castle
After terrible events, the world has changed forever, and the knights who guarded the castle now bring death to all living things. 
You have to do the almost impossible, try to get out of this castle alive.



## Getting Started
#### Installing dependencies

Dependence | How to install
-----------|---------------
1. sudo|`$ sudo apt update`
2. g++/make|`$ sudo apt-get install build-essential`
3. cmake|[Guide](https://vitux.com/how-to-install-cmake-on-ubuntu-18-04/)
4. python3|`$ sudo apt-get install python3.8`
5. clang-format|`$ sudo apt install clang`
6. CryptoPP|`$ sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils`

## Run The Game
Enter following command in the terminal: `make`.

This command automatically does:
1. Clean previous build `make clear`
2. Reload CMake `make reload`
3. Style-guide check `make lint`
4. Compile `make build`
5. Run the game `make exec`

## Built With
- C++14 language 
- [BearLibTerminal](http://foo.wyrd.name/en:bearlibterminal/) - Symbolic/Graphic library
- [CryptoPP 8.2](https://www.cryptopp.com/) Cryptographic library

## Authors
- Michael Linker - *Entire work* - [MrBattary](https://github.com/MrBattary)

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Added Features
1. The basic system of characteristics (Attack, Defense, Health).
2. The player has an inventory in which he wears armor and weapons.
3. Armor and weapons have their own names.
4. Armor and weapons have characteristics.The weapon increases attack, and the armor increases defense, but decreases attack.
5. Enemies have inventory in which they wear armor and weapons.
6. Three types of enemies:
    
    6.1. Red-common enemies, weak weapons, lack of armor. The basic AI.

    6.2. Blue-rare enemies, medium weapons, medium armor. An advanced AI.

    6.3. Silver is an elite enemy, elite weapon, elite armor. Very advanced AI.
7. Having found the player, the enemies try to catch up with him, if they catch up with him, then there is a battle.
8. GUI with inventory/help/pause/log boxes.