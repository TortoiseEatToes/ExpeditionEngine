#pragma once

#include "../../../Expedition Engine/Scene Components/Game Object/GameObject.h"
#include "../../../Expedition Engine/Math/Matrix/Matrix4F.h"
#include "UpdateBallPosition.h"
#include "../Collision/BallCollision.h"

class ParticleEmitter;

class BallManager : public GameObject
{
public:
	BallManager() = delete;
	BallManager(const SceneName& sceneToExistIn);
	BallManager(BallManager&&) = delete;
	BallManager(const BallManager&) = delete;
	const BallManager& operator =(BallManager&&) = delete;
	const BallManager& operator =(const BallManager&) = delete;
	~BallManager();

	void OnSceneEnter() override;
	void OnSceneExit() override;

private:

	const static float randMaxInv;

	const static int numOfBalls = 300;

	Matrix4F* worldMatrices;
	Vector4F* velocityVectors;

	ParticleEmitter** particleEmitters;

	GraphicsObject go_Ball;
	UpdateBallPosition updateBall;
	BallCollision** ballCollision;
};

