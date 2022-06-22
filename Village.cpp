/**
 * @author ! Pixel
 *
 */





/**
 * @brief Checks if a iron golem can spawn within the boundary box by cycling though all the surface area positions in the 16x6x16 area
 * 
 * @param Village *
 * @return boolean if a golem can spawn within the boundary box
 */
bool Village::canSpawnAt(Village * this, int a2, int a3, int a4, int a5, int a6, int a7) {

  Dimension * dimension = Level::getDimension(this -> mLevel, VanillaDimensions::Overworld);
  BlockSource * blockSource = Dimension::getBlockSourceDEPRECATEDUSEPLAYERREGIONINSTEAD(dimension);
  Block * block01 = BlockSource::getBlock(blockSource, a2, a3 - 1, a4);
  Block * block02;
  if (!Block::isSolid(block01))
    return 0;

  bool bool1 = (a5 >= 1 ? (a6 < 1) : (a5 < 1))
  if (!bool1) {
    int v15 = a4 - a7 / 2;
    int v16 = a2 - a5 / 2;
    int v20 = v16 + a5;
    int v21 = a3 + a6;

    for (int i = v16; v18 = a3, i < v20; i++) {
      for (; v17 = v15, v18 < v21; v18++) {
        for (; v17 < v15 + a7; v17++) {
          block02 = BlockSource::getBlock(blockSource, v16, v18, v17);
          if (Block::isSolid(block02))
            return false;
        }
      }
    }
    return true;
  }
}

bool Village::canSpawnAtBlockPos(Village *this, const BlockPos *a2, const BlockPos *a3){ //in code it is just Village::canSpawnAt
 
  return Village::canSpawnAt(this, *a2, *(a2 + 1), *(a2 + 2), *a3, *(a3 + 1), *(a3 + 2));

}

/**
 * @brief Counts the golems inside the boundry box 
 * 
 * @param Village * 
 * @return int - count
 */
int Village::countGolem(Village *this){
  AABB *vBoundryBox [32]; // in windows 1.6 it was 8 but imma leave it as 32 

  Dimension *dimension = Level::getDimension(this->mLevel, VanillaDimensions::Overworld);
  BlockSource blockSource = Dimension::getBlockSourceDEPRECATEDUSEPLAYERREGIONINSTEAD(dimension);
  float vRadius = this->mRadius;
  AABB::AABB(vBoundryBox,
     mCenter.z - vRadius,
     mCenter.y - 4.0,
     mCenter.x - vRadius,
     vRadius + (mCenter.z),
     mCenter.y + 4.0,
     mCenter.x + vRadius);
    Actor *actor = BlockSource::fetchEntities(blockSource,ActorType::IronGolem, vBoundryBox ,(Actor *)0x0); //ActorType::IronGolem enum = 0x314 = 788
    int result = (actor[1] - *actor) >> 2;
    this->mGolemCount = result; //mGolemCount
    return result;
}


/**
 * @brief returns true or false if the parameters are met to expand the village population
 *
 */
bool Village::checkNeedMoreVillagers(Village * this) {
  if ( * (this -> mNoBreedTimer) && * (this -> mGameTick) - (this -> mNoBreedTimer) < 3600)
    return false;

  DoorInfo doorInfo = * (this -> mDoorInfo);
  int populationSize = * (this -> mPopulationSize);
  bool result = false;
  /**
   * @note: the windows 1.6 of this method includes an unknown filed `filed_0x8`
   * for this I have deduced that it has to be some sort of count value or struct of `mDoorInfos` that returns an integer value of the number of doors 
   *     original  windows 1.7: `&(this->mDoorInfos).field_0x8 - &this->mDoorInfos >> 3)`
   * @TODO: find the actual name not just `pCount`
   */
  int dCount = (doorInfo.pCount - doorInfo >> 2);
  return v4 < (dCount <= 3 ? 3 : dCount);
}


