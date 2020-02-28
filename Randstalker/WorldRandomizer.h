#pragma once

#include <vector>
#include <string>
#include <random>

#include "ItemCodes.h"
#include "ItemSourceCodes.h"
#include "RegionCodes.h"
#include "AbstractItemSource.h"
#include "RandomizerOptions.h"
#include "Item.h"
#include "World.h"
#include "WorldRegion.h"

class NoAppropriateItemSourceException : public std::exception {};

class WorldRandomizer
{
public:
	WorldRandomizer(World& world, const RandomizerOptions& options);
	~WorldRandomizer() {}

	void randomize();

private:
	void setSpawnPoint();
	void randomizeGoldValues();

//	void randomizeDarkRooms();

	void initPriorityItems();
	void initFillerItems();
	void randomizeItems();

	std::vector<WorldRegion*> evaluateReachableRegions(const std::vector<Item*>& playerInventory, std::vector<Item*>& out_keyItems, std::vector<AbstractItemSource*>& out_reachableSources);
	
	void fillSourcesWithPriorityItems();
	void fillSourcesWithFillerItems(std::vector<AbstractItemSource*>::iterator begin, std::vector<AbstractItemSource*>::iterator end);

	void writeItemSourcesBreakdownInLog();

	void randomizeHints();
	std::string getRandomHintForItem(Item* item);

	void randomizeTiborTrees();

private:
	World& _world;
	const RandomizerOptions& _options;

	std::ofstream _logFile;
	std::mt19937 _rng;

	std::vector<Item*> _priorityItems;
	std::vector<Item*> _fillerItems;
	std::vector<Item*> _keyItems;
};
