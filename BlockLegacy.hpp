#pragma once

#include <map>
#include <string>
#include <memory>
#include "../lib/mod.h"
#include "../hook/SymHook.h"

/**
 * @author Luke7720
 * Written for 1.6.0 Windows BDS to be used in DLL modding
 * These classes are mostly divided in 3 sections: members, new methods and existing methods. New methods will
 * contain custom getters & setters written using offsets taken from an IDA database corresponding to the
 * version these classes are written for. Existing methods will mostly contain SYMCALLs though I'm hoping we
 * can slowly reconstruct them as we go. Finally, members will contain a list of the class' memebers under
 * the private access specifier.
 */

class BlockLegacy {
public:
	// New Methods
    std::string* getDescriptionId()	{
        return	reinterpret_cast<std::string*>(reinterpret_cast<VA>(this) + 0x08);
    }

    std::string* getRawNameId()	{
        return	reinterpret_cast<std::string*>(reinterpret_cast<VA>(this) + 0x28);
    }

	bool canSlide() {
        return * reinterpret_cast<bool*>(reinterpret_cast<VA>(this)	+ 0x6C);
    }

	float getBlastResistance() {
        return *reinterpret_cast<float*>(reinterpret_cast<VA>(this)	+ 0xA0);
    }

	bool isSolid() {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this)	+ 0xAA);
    }

	bool isTrapdoor() {
        return *reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0xAD);
    }

	float getTranslucency() {
        return *reinterpret_cast<float*>(reinterpret_cast<VA>(this)	+ 0xB0);
    }

    int getFlameOdds() {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0xB8);
    }

    int getBurnOdds() {
        return *reinterpret_cast<int*>(reinterpret_cast<VA>(this) + 0xBC);
    }
	// Existing Methods
	bool shouldTick() const	{
        return SYMCALL(bool, MD5_e9ae7a92708b0d37aaa9bbe13c30e362, this);
    }

	bool canContainLiquid()	const {
        return SYMCALL(bool, MD5_9c40a8978dc6608c8b914d81ab4df17a, this);
    }

	BlockLegacy* setExplodeable(float explosionResistance) {
        return SYMCALL(BlockLegacy*, MD5_50b6adeb3bb64b27b2b613582e2832bb, this, explosionResistance);
    }

    BlockLegacy* setDestroyTime(float destroySpeed)	{
        return SYMCALL(BlockLegacy*, MD5_3777fa572ad04b63dd5287b4f4d49fd3, this, destroySpeed);
    }

    BlockLegacy* setFriction(float f) {
        return SYMCALL(BlockLegacy*, MD5_1d60afb5a9247c9ea06846f23ebdd89e, this, f);
    }

    BlockLegacy* resetBitsUsed() {
        return SYMCALL(BlockLegacy*, MD5_51f0b2064925b4a78eda857c6d99858b, this);
    }

    BlockLegacy* setAllowsRunes(bool interference) {
        return SYMCALL(BlockLegacy*, MD5_4c35ac1033c72bb0295b4b9249d20af8, this, interference);
    }

	bool canBeUsedInCommands(bool, bool allowExperimental) const {
        return SYMCALL(bool, MD5_dc48e633628d9cc1e627c0e92cd364a3, this, allowExperimental);
    }

	float getThickness() const {
        return SYMCALL(float, MD5_6ffc1124b5ab13a24d9b4501d9436514, this);
    }
};