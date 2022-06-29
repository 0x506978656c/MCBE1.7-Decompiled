#pragma once

#include <vector>
#include <cstdint>
#include "../lib/mod.h"
#include "../hook/SymHook.h"
#include "Pos.hpp"
#include "BlockActor.hpp"
#include "BlockSource.hpp"
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

class PistonBlockActor : BlockActor
{
public:
	enum PistonState : __int8
	{
		Retracted = 0x0,
		Expanding = 0x1,
		Expanded = 0x2,
		Retracting = 0x3,
	};

	using BPVEC = std::vector<BlockPos>;
	// New Methods
	bool isSticky()	const {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0xC8);
    }

	float getProgress()	const {
        return *reinterpret_cast<float*>(reinterpret_cast<VA>(this) + 0xCC);
    }

	float getLastProg() const {
        return *reinterpret_cast<float*>(reinterpret_cast<VA>(this) + 0xD0);
    }

    __int8 oldState() const	{
        return *reinterpret_cast<__int8*>(reinterpret_cast<VA>(this) + 0xD6);
    }

    __int8 getState() const	{
        return *reinterpret_cast<__int8*>(reinterpret_cast<VA>(this) + 0xD7);
    }

    __int8 newState() const	{
        return *reinterpret_cast<__int8*>(reinterpret_cast<VA>(this) + 0xD8);
    }

	bool verifyArm() const {
        return * reinterpret_cast<bool*>(reinterpret_cast<VA>(this)	+ 0xD9);
    }

	BPVEC* getAttachhedBlocks() const {
        return reinterpret_cast<BPVEC*>(reinterpret_cast<VA>(this) + 0xE0);
    }

	uint64_t getLastTick() const{
        return *reinterpret_cast<uint64_t*>(reinterpret_cast<VA>(this) + 0x110);
    }
	// Existing Methods
	bool isMovable(BlockSource& region) const {
        return SYMCALL(bool, MD5_b6c1388f283963e5acff32481e7f4f02, this, region);
    };

    const BlockPos* getFacingDir(BlockSource& region) const	{
        return SYMCALL(const BlockPos*, MD5_868fe3634e2f9f387a8990eca6cdac61, this, region);
    };

	bool _checkAttachedBlocks(BlockSource& region) const {
        return SYMCALL(bool, MD5_d7a00ac2d9adec414a3662b847fe2d7c, this, region);
    };

	bool _hasBlockAttached(BlockPos const& blockPos) const {
        return SYMCALL(bool, MD5_6f6187f91ebfd7ac5108b1391acfd722, this, blockPos);
    };
};