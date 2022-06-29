#pragma once

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

class AABB {
public:
    // New Methods
	Vec3* getMin() const {
        return reinterpret_cast<Vec3*>(reinterpret_cast<VA>(this));
    }

	Vec3* getMax() const {
        return reinterpret_cast<Vec3*>(reinterpret_cast<VA>(this) + 0xC);
    }

	bool isEmpty() const {
        return * reinterpret_cast<bool*>(reinterpret_cast<VA>(this) + 0x18);
    }
};