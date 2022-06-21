/**
 * @author ! Pixel
 *
 */

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
