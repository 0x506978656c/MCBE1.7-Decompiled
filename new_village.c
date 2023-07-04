// decompiled straight no changes what so ever 


void Villages::tick(Villages * this) {
  this -> mTickCount++;

  Dimension * dimension = Level::getDimension(this -> mLevel, Overworld);
  if (dimension != nullptr) {
    for (auto village: this -> mVillages) {
      village -> tick(this -> mTickCount);
    }
  }

  for (auto vil = this -> mVillages.begin(); vil != this -> mVillages.end();) { 
    if (( *vil) -> hasExpired()) {
      vil = this -> mVillages.erase(vil);
    } else {
      ++vil;
    }
  }

  if (!this -> mFindDoorQueries.empty()) {
    addDoorInfoWithinRadius(this, & this -> mFindDoorQueries.back());
    this -> mFindDoorQueries.pop_back();
  }

  processNextVillageQuery(this);

  for (auto &doorInfo: this -> mUnclustered) {
    assignDoorOrCreateVillage(this, & doorInfo);
  }

  this -> mUnclustered.clear();

  if (this -> mTickCount % 400 == 0) {
    this -> mDirty = 1; //idk what this is for xD
  }
}


void Village::tick(int gameTick) {
  Level * level = mLevel;
  Dimension * dimension = Level::getDimension(level, Overworld);

  if (dimension != nullptr) {
    bool updateCenter = false;
    uint32_t randomInt = Random::_genRandInt32( & level -> mRandom);

    for (auto doorInfo: mDoorInfos) {
      if (randomInt % 50 == 0) {
        doorInfo -> mBookings = 0;
      }

      Block * block = BlockSource::getBlock(dimension -> mBlockSource, & doorInfo -> mPosition);

      if (((block -> mLegacyBlock -> mProperties >> 10) & 1) == 0 ||
        block -> mLegacyBlock -> mMaterial -> mType != Wood ||
        (gameTick - doorInfo -> mTimeStamp) > 1200) {
        updateCenter = true;
        Villages::removeDoorInfo((Villages * ) level -> mVillages, doorInfo);
      }
    }

    if (updateCenter) {
      calcInfo(this);
    }
  }

  if (!mAggressors.empty()) {
    for (auto it = mAggressors.begin(); it != mAggressors.end();) {
      ActorUniqueID actorID = it -> first;
      Actor * actor = findActorByID(actorID);

      if (actor != nullptr && actor -> isAlive() && (gameTick - it -> second) < 301) {
        ++it;
      } else {
        it = mAggressors.erase(it);
      }
    }
  }

  if (gameTick % 30 == 0) {
    Dimension * overworldDimension = Level::getDimension(mLevel, Overworld);
    if (overworldDimension != nullptr) {
      int golemCount = 0;
      vector < Actor * > * golems = BlockSource::fetchEntities(overworldDimension -> mBlockSource, IronGolem, nullptr, nullptr);
      if (golems != nullptr) {
        golemCount = static_cast < int > (golems -> size());
      }
      mGolemCount = golemCount;
    }
  }

  LevelData * levelData = (mLevel -> mLevelData).mLevelDataFromLevel;
  if (levelData == nullptr) {
    levelData = & (mLevel -> mLevelData).mLevelDataFromDisk;
  }

  if (levelData != nullptr && levelData -> hasRule("mobGriefing") && levelData -> getBool("mobGriefing") &&
    mGolemCount < mVillagers.size() / 10 && mDoorInfos.size() > 5 && (gameTick % 7000) == 0) {
    BlockPos spawnPos;
    Actor * golem = nullptr;
    if (findRandomSpawnPos(this, & mCenter, & mCenter, & spawnPos)) {
      Dimension * overworldDimension = Level::getDimension(mLevel, Overworld);
      if (overworldDimension != nullptr) {
        golem = spawnGolem(overworldDimension, spawnPos);
      }
    }

    if (golem != nullptr) {
      mAggressors[golem -> getUniqueID()] = gameTick;
    }
  }
}
