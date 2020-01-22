#pragma once

#include <cstdint>
#include <string>
#include "GameROM.h"

class OutsideTreeMap {
public:
    OutsideTreeMap(const std::string& name, uint32_t leftEntranceMapAddress, uint32_t rightEntranceMapAddress, uint16_t treeMapID) :
        _name(name),
        _leftTreeEntranceMapAddress(leftEntranceMapAddress),
        _rightTreeEntranceMapAddress(rightEntranceMapAddress),
        _treeMapID(treeMapID)
    {}

    uint16_t getTree() const { return _treeMapID; }
    void setTree(uint16_t treeMapID) { _treeMapID = treeMapID; }
    const std::string& getName() const { return _name; }

    void writeToROM(GameROM& rom)
    {
        rom.setWord(_leftTreeEntranceMapAddress, _treeMapID);
        rom.setWord(_rightTreeEntranceMapAddress, _treeMapID);
    }

private:
    std::string _name;
    uint32_t _leftTreeEntranceMapAddress;
    uint32_t _rightTreeEntranceMapAddress;
    uint16_t _treeMapID;
};
