// so the ai decompiler wrote this and i kid u not pulled values from the stars 





void Village::tick()
{
    if (this->mDoorInfos.empty())
    {
        this->remove();
        return;
    }

    bool hasIronGolem = this->hasIronGolem();

    for (auto& doorInfoPair : this->mDoorInfos)
    {
        std::unique_ptr<DoorInfo>& doorInfo = doorInfoPair.second;

        if (doorInfo->isDetachedFromVillageFlag())
            continue;

        if (doorInfo->getDoorBlockPos().isOutsideWorldBorder())
        {
            doorInfo->setDetachedFromVillageFlag(true);
            hasIronGolem = false;
            continue;
        }

        if (!doorInfo->isDoorStillValid())
        {
            hasIronGolem = false;
            continue;
        }

        int32_t villagersBehindDoors = doorInfo->getVillagersBehindCount();

        if (!hasIronGolem && villagersBehindDoors < 6)
        {
            int32_t ironGolemCount = this->mIronGolemCount;
            int32_t villagersCount = this->getVillagersCount();
            int32_t requiredDoors = (villagersCount - ironGolemCount) / 35;

            if (villagersCount % 35 != 0)
                ++requiredDoors;

            if (villagersBehindDoors <= requiredDoors)
            {
                if (this->trySpawnGolem())
                    hasIronGolem = true;
            }
        }

        doorInfo->tick();
    }

    if (!hasIronGolem)
    {
        int32_t ironGolemCount = this->mIronGolemCount;
        int32_t villagersCount = this->getVillagersCount();

        if (villagersCount - ironGolemCount >= 70 && this->tickSinceLastGolemSpawn >= 400)
        {
            int32_t validDoorsCount = this->getValidDoorsCount();

            if (validDoorsCount > 0)
            {
                int32_t requiredDoors = (villagersCount - ironGolemCount) / 35;

                if (villagersCount % 35 != 0)
                    ++requiredDoors;

                if (this->mNumIronGolems < requiredDoors)
                    this->trySpawnGolem();
            }
        }
    }
}

bool Village::hasIronGolem()
{
    return this->mNumIronGolems > 0;
}

bool Village::trySpawnGolem()
{
    Vec3 pos = this->mAccCenter;
    pos.x += static_cast<float>((Random::_genRandInt32(&this->mLevel->mRandom) % 2 - 1) * 2);
    pos.y += 2.0f;
    pos.z += static_cast<float>((Random::_genRandInt32(&this->mLevel->mRandom) % 2 - 1) * 2);

    auto entity = new IronGolemEntity(this->mLevel);
    entity->setPos(pos);
    entity->setHomePos(this->mAccCenter);
    this->mLevel->addEntity(entity);
    this->mIronGolemCount++;
    return true;
}
