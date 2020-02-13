//////////////////////////////////////////////////////////////////////////////////////////
//
//		RANDSTALKER ROM GENERATOR
//
// ---------------------------------------------------------------------------------------
//
//		Developed by:	Dinopony (@DinoponyRuns)
//		Version:		v0.9e
//
// ---------------------------------------------------------------------------------------
//
//	Special thanks to the whole Landstalker speedrunning community for being supportive
//	and helpful during the whole process of developing this!
//
//
//  Command line syntax:
//		randstalker [args]
//
//	Common parameters:
//		--inputRom="value"		===> Path to the game ROM used as input for the randomization (this file will only be read, not modified).
//		--outputRom="value"		===> Path where the randomized ROM will be put, defaults to 'output.md' in current working directory.
//		--seed="value"			===> Random seed (integer value or "random") used to alter the game. Using the same seed twice will produce the same result.
//		--outputLog="value"		===> Path where the seed log will be put, defaults to 'randstalker.log' in current working directory.
//		--noPause				===> Don't ask to press a key at the end of generation (useful for automated generation systems)
//
//	Randomization options:
//		--shuffleTrees			===> Randomize Tibor trees
//		--noArmorUpgrades		===> Don't use armor upgrades, just place vanilla armors randomly
//		--randomSpawn			===> randomize spawn point between Massan, Gumi and Ryuma
//		--noRecordBook			===> Record Book not available in inventory
//
//////////////////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <string>
#include <iostream>

#include "GameROM.h"
#include "GameAlterations.h"
#include "Tools.h"
#include "World.h"
#include "WorldRandomizer.h"

constexpr auto RELEASE = "0.9e";

GameROM* getInputROM(std::string inputRomPath)
{
	GameROM* rom = new GameROM(inputRomPath);
	while (!rom->isValid())
	{
		delete rom;
		if (!inputRomPath.empty())
			std::cout << "[ERROR] ROM input path \"" << inputRomPath << "\" is wrong, and no ROM could be opened this way.\n\n";
		std::cout << "Please specify input ROM path (or drag ROM on Randstalker.exe icon before launching): ";
		std::getline(std::cin, inputRomPath);
		rom = new GameROM(inputRomPath);
	}

	return rom;
}

int main(int argc, char* argv[])
{
	std::cout << "======== Randstalker v" << RELEASE << " ========\n\n";

	RandomizerOptions options(argc, argv);

	GameROM* rom = getInputROM(options.getInputROMPath());


	// ------------ Randomization -------------
	// Perform game changes unrelated with the randomization part
	alterROM(*rom, options);
	
	// Create a replica model of Landstalker world, randomize it and save it to the ROM	
	World landstalkerWorld(options);

	WorldRandomizer randomizer(landstalkerWorld, options);
	randomizer.randomize();

	landstalkerWorld.writeToROM(*rom);
	rom->saveAs(options.getOutputROMPath());

	std::cout << "Randomized rom outputted to \"" << options.getOutputROMPath() << "\".\n\n";

	if ( options.mustPause() )
	{
		std::cout << "Press any key to exit.";
		std::string dummy;
		std::getline(std::cin, dummy);
	}

	return 0;
}
