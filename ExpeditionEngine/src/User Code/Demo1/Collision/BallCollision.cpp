#include "BallCollision.h"
#include "..//../..//Expedition Engine/Math/Vector/Vector4F.h"
#include "..//../..//Expedition Engine/Math/Matrix/Matrix4F.h"
#include "../../../Expedition Engine/Scene Components/Collision/Volumes/CV_Plane.h"
#include "../../../Expedition Engine/Scene Components/Collision/Volumes/CV_Sphere.h"


BallCollision::BallCollision(const SceneName& sceneToExistIn)
{
	registeredScene = sceneToExistIn;
	bounceCounter = 0;

}

BallCollision::~BallCollision()
{
}

void BallCollision::Collision(CollisionComponent& otherVolume, CV_Sphere& otherSphere)
{
	bounceCounter++;

	BallCollision* pTake2 = (BallCollision*) &otherVolume;

	Vector4F otherCenter = otherSphere.GetCenter();
	CV_Sphere* pThisVolume = (CV_Sphere*) GetCollisionVolume();

	Vector4F dircBetweenCenters = pThisVolume->GetCenter() - otherCenter;

	*velocityVector = dircBetweenCenters.NormCopy();

	if (bounceCounter > 20) {
		*velocityVector *= 5;
		bounceCounter = 0;
	}


	(*velocityVector).W() = 1;




}

void BallCollision::Collision(CollisionComponent& otherVolume, CV_Plane& otherPlane)
{
	bounceCounter++;

	velocityVector->RotateAxisAngle(otherPlane.GetNormal(), 3.0f);
	*velocityVector *= -1.0f;

	*velocityVector *= .8f;
	//*velocityVector += otherPlane.GetNormal() * .01f;

	if (bounceCounter > 5) {
		*velocityVector *= 5.0f;
		bounceCounter = 0;
	}

	int norm = static_cast<int>(velocityVector->MagSqr());

	if (norm > 25) {
		velocityVector->Norm();
		*velocityVector *= 5;
	}

	(*velocityVector).W() = 1;

	(*worldMatrix) *= Matrix4F(TRANS, (*velocityVector));
}