#pragma once

#include "Village.hpp"
#include "Pos.hpp"

/**
 * @author Luke7720
 * Written for 1.6.0 Windows BDS to be used in DLL modding
 * These classes are mostly divided in 3 sections: members, new methods and existing methods. New methods will
 * contain custom getters & setters written using offsets taken from an IDA database corresponding to the
 * version these classes are written for. Existing methods will mostly contain SYMCALLs though I'm hoping we
 * can slowly reconstruct them as we go. Finally, members will contain a list of the class' memebers under
 * the private access specifier.
 */

class DoorInfo
{
public:
    // New Methods
    Village* getVillage() const {
        return reinterpret_cast<Village*>(reinterpret_cast<VA>(this) + 0x08);
    }

    BlockPos* getPosition    () const {
        return reinterpret_cast<BlockPos*>(reinterpret_cast<VA>(this) + 0x10);
    }

    int getTimestamp() const -> int {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x30);
    }
};
