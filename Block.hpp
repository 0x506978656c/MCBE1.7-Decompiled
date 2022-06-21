#pragma once

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

class Block {
public:
    const unsigned __int8 getData() {
        return *reinterpret_cast<const unsigned __int8>(reintepret_cast<VA>(this) + 0x8);
    }

    const BlockLegacy* getLegacyBlock() {
        return reinterpret_cast<const BlockLegacy*>(reintepret_cast<VA>(this) + 0x10);
    }

    CompoundTag getSerializationId() {
        return *reinterpret_cast<CompoundTag>(reintepret_cast<VA>(this) + 0x18);
    }

    unsigned int getRuntimeId() {
        return *reinterpret_cast<unsigned int>(reintepret_cast<VA>(this) + 0x30);
    }

    void setData(const unsigned __int8  param_1) {
        *reinterpret_cast<const unsigned __int8>(reintepret_cast<VA>(this) + 0x8) = param_1;
    }

    void setLegacyBlock(const BlockLegacy * param_1) {
        reinterpret_cast<const BlockLegacy *>(reintepret_cast<VA>(this) + 0x10) = param_1;
    }

    void setSerializationId(CompoundTag  param_1) {
        *reinterpret_cast<CompoundTag>(reintepret_cast<VA>(this) + 0x18) = param_1;
    }

    void setRuntimeId(unsigned int  param_1) {
        *reinterpret_cast<unsigned int>(reintepret_cast<VA>(this) + 0x30) = param_1;
    }
};
