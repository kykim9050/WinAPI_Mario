#include "ContentsFunction.h"
#include "CollisionMap.h"

UContentsFunction::UContentsFunction()
{
}

UContentsFunction::~UContentsFunction()
{
}

UWindowImage* UContentsFunction::GetCollisionMapImg()
{
	return UCollisionMap::GetCollisionMapImg();
}


