#pragma once

#include <string>
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

struct Vec3
{
	float x;
	float y;
	float z;
};

const Vec3 VEC3ZERO = SYM_OBJECT(Vec3, MD5_b0f8f7222be1399ac971e8279640e9a8);

class BlockPos
{
public:
	int x{};
	int y{};
	int z{};

	std::string toString() const {
        return SYMCALL(std::string, MD5_08038beb99b82fbb46756aa99d94b86f, this);
    }
};