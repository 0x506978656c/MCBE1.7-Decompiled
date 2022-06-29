#pragma once

#include "../mod.h"
#include "Pos.hpp"
#include "AABB.hpp"
#include "BlockSource.hpp"
#include "Block.hpp"
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

class BlockActor
{
public:
    enum BlockActorRendererId : __int32
    {
        TR_DEFAULT_RENDERER = 0x0,
        TR_CHEST_RENDERER = 0x1,
        TR_SIGN_RENDERER = 0x2,
        TR_MOBSPAWNER_RENDERER = 0x3,
        TR_SKULL_RENDERER = 0x4,
        TR_ENCHANTER_RENDERER = 0x5,
        TR_PISTONARM_RENDERER = 0x6,
        TR_ITEMFRAME_RENDERER = 0x7,
        TR_MOVINGBLOCK_RENDERER = 0x8,
        TR_CHALKBOARD_RENDERER = 0x9,
        TR_BEACON_RENDERER = 0xA,
        TR_ENDGATEWAY_RENDERER = 0xB,
        TR_ENDERCHEST_RENDERER = 0xC,
        TR_STRUCTUREBLOCK_RENDERER = 0xD,
        TR_SHULKERBOX_RENDERER = 0xE,
        TR_COMMANDBLOCK_RENDERER = 0xF,
        TR_BED_RENDERER = 0x10,
        TR_BANNER_RENDERER = 0x11,
        TR_CONDUIT_RENDERER = 0x12,
    };
    // New Methods
    const Block* getBlock() const {
        return reinterpret_cast<const Block*>(reinterpret_cast<VA>(this + 0x10);
    }

    BlockPos* getPosition() const {
        return reinterpret_cast<BlockPos*>(reinterpret_cast<VA>(this) + 0x2C);
    }

    AABB* getAABB()	const {
        return reinterpret_cast<AABB*>(reinterpret_cast<VA>(this) + 0x38);
    }

    int getData() const {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0x54);
    }

    BYTE* getType() const {
        return reinterpret_cast<BYTE*>(reinterpret_cast<VA>(this) + 0x58);
    }

    __int32 getRndererId() const {
        return *reinterpret_cast<__int32*>(reinterpret_cast<VA>(this) + 0x5C);
    }

    bool clientOnly() const {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0xA4);
    }

    bool canRndrName() const {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0xA7);
    }

    bool changed() const {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0xC0);
    }
    // Existing Methods
    int getRepairCost()	const {
        return SYMCALL(int,	MD5_cba19bdd9ee779b7dd2e6ada25683c8d);
    }

    std::string getCustomName()	const {
        return SYMCALL(std::string, MD5_5d96cf82ce5f44eef4e2217972440f16);
    }
    bool isMovable(BlockSource& region) const {
        return SYMCALL(bool, MD5_acf0aa2384d9618f8aa1af9f08105b1c);
    }

    bool isCustomNameSaved() const {
        return SYMCALL(bool, MD5_3f10a28bb6ade8d75ae77441093f9335);
    }
};