#pragma once

#include <vector>
#include <unordered_set>
#include "placeholders.hpp"

/**
 * @author Luke7720
 * Written for 1.6.0 Windows BDS to be used in DLL modding
 * These classes are mostly divided in 3 sections: members, new methods and existing methods. New methods will
 * contain custom getters & setters written using offsets taken from an IDA database corresponding to the
 * version these classes are written for. Existing methods will mostly contain SYMCALLs though I'm hoping we
 * can slowly reconstruct them as we go. Finally, members will contain a list of the class' memebers under
 * the private access specifier.
 */

class Village
{
public:
    // DoorInfoPointerVectorPointer && ActorUniqueIDUnorderedSetPointer
    using DIPVECP = std::vector<DoorInfo*>*;
    using AUUSETP = std::unordered_set<ActorUniqueID>*;
    // New Methods
    DIPVECP getDoorInfos() const {
        return reinterpret_cast<DIPVECP>(reinterpret_cast<VA>(this) + 0x008);
    }

    AUUSETP getVillagers() const {
        return reinterpret_cast<AUUSETP>(reinterpret_cast<VA>(this) + 0x020);
    }

    BlockPos* getCenter() const {
        return reinterpret_cast<BlockPos*>(reinterpret_cast<VA>(this) + 0x06C);
    }

    int getRadius() const {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x078);
    }

    int getGameTick() const {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x080);
    }

    int getNoBreedTimer() const {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x084);
    }

    int getGolemCount() const {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x108);
    }
    // Existing Methods
};
