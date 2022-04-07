#include "CollisionTest.h"

CollisionTest::CollisionTest()
{
	registeredScene = Scene1;
}

CollisionTest::~CollisionTest()
{
}

void CollisionTest::Collision(CollisionComponent& otherVolume, CV_Sphere& otherSphere)
{
	//I don't know
}

void CollisionTest::Collision(CollisionComponent& otherVolume, CV_Plane& otherPlane)
{
	//Do something
}
