#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "DoorInfo.hpp"
#include "Village.hpp"
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

class Villages : SavedData
{
private:
    Level* mLevel;
    std::vector<BlockPos> mFindDoorQueries;
    std::unordered_set<BlockPos> mFindVillageQueries;
    std::vector<std::unique_ptr<DoorInfo>> mUnclustered;
    std::unordered_set<std::shared_ptr<Village>> mVillages;
    std::unordered_map<BlockPos,std::unique_ptr<DoorInfo>> mDoorInfos;
    int mTickCount;
public:
    // IM NOT REPLICATING ANY OF THESE AND I AINT GONNA BOTHER TESTING SO SOMEONE ELSE DO please
    std::weak_ptr<Village>* fetchClosestVillage(std::weak_ptr<Village>* result, const BlockPos* position, int maxDist);
    std::weak_ptr<Village>* fetchClosestVillage2D(std::weak_ptr<Village>* result, const BlockPos* position, int maxDist);
    std::weak_ptr<Village>* _fetchClosestVillage(std::weak_ptr<Village>* result, const BlockPos* position, int maxDist, bool twoD);
    std::weak_ptr<Village>* fetchVillagersVillage(std::weak_ptr<Village>* result, const ActorUniqueID *villager);
    // in theory none of the functions above should have the result parameter but idk, imma listen to ida
    DoorInfo* getDoorInfo(const BlockPos* pos);
}