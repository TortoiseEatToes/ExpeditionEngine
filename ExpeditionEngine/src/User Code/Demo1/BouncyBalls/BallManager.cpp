#include "BallManager.h"
#include "..//..//..//Expedition Engine/Graphics/Model/Managers/ModelManager.h"
#include "..//..//..//Expedition Engine/Graphics/Model/Managers/TextureManager.h"
#include "../../../Expedition Engine/Scene Components/Particle Emitter/ParticleEmitter.h"

BallManager::BallManager(const SceneName& sceneToExistIn)
	:GameObject(sceneToExistIn), go_Ball(sceneToExistIn, ModelManager::Get(ModelName::SphereModel), numOfBalls)
{
	particleEmitters = new ParticleEmitter*[numOfBalls];

	worldMatrices = new Matrix4F[numOfBalls];
	velocityVectors = new Vector4F[numOfBalls];
	ballCollision = new BallCollision*[numOfBalls];

	Vector4F color;

	for (int i = 0; i < numOfBalls; i++) 
	{
		particleEmitters[i] = new ParticleEmitter(sceneToExistIn, ParticleName::Fire);


		//particleEmiitters[i]->SetEmitterTypeColorLight(ModelManager::Get(ModelName::ParticleModel));

		worldMatrices[i] = (Matrix4F(TRANS, Vector4F(0, 50, 0, 1)) *Matrix4F(SCALE, 1.0f)).TransposeCopy();

		go_Ball.SetWorld(worldMatrices[i], i);

		velocityVectors[i] = Vector4F((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - .5f,
			(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - .5f,
			(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - .5f, 1);

		color = Vector4F(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
			static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1);

		go_Ball.SetMaterial(color, color, Vector4F(.5, .5, .5, static_cast <float> (rand()) / static_cast <float> (RAND_MAX)), i);
		particleEmitters[i]->SetParticleColorTint(color.X(), color.X() + 0.0001f, color.Y(), color.Y() + 0.0001f, color.Z(), color.Z() + 0.0001f, 0.999f, 1.1f);

		//color = 2.0 * color;
		color.W() = 1;

		//particleEmitters[i]->SetParticleColorTint(color.X(), color.X() + 0.1f, color.Y(), color.Y() + 0.1f, color.Z(), color.Z() + 0.1f, 1, 1.01f);

		ballCollision[i] = new BallCollision(sceneToExistIn);
		ballCollision[i]->velocityVector = &(velocityVectors[i]);
		ballCollision[i]->worldMatrix = &(worldMatrices[i]);
	}

	updateBall.worldMatrices = &worldMatrices;
	updateBall.velocityVects = &velocityVectors;
	updateBall.go_Ball = &go_Ball;
	updateBall.ballCollision = ballCollision;
	updateBall.particleEmitters = particleEmitters;
	
	updateBall.numOfBalls = numOfBalls;


}

BallManager::~BallManager()
{
	for (int i = 0; i < numOfBalls; i++) 
	{
		delete ballCollision[i];
		//delete particleEmiitters[i];;
	}

	//delete[] particleEmiitters;
	delete[] ballCollision;
	delete[] worldMatrices;
	delete[] velocityVectors;
}

void BallManager::OnSceneEnter() 
{
	for (int i = 0; i < numOfBalls; i++) 
	{
		ballCollision[i]->SetCollisionVolumeSphere();
		ballCollision[i]->SetWorld(worldMatrices[i]);

		ballCollision[i]->StartDetectingCollision(GetRegisteredScene());
		//particleEmiitters[i]->RegisterToScene();

		particleEmitters[i]->SetBurstLifetime(0.2f, 0.3f);
		particleEmitters[i]->StartSpawnParticleBurstRepeating(3, 0.05f);
	}

	updateBall.StartUpdating(GetRegisteredScene());
	go_Ball.StartDrawingColorLight();
}

void BallManager::OnSceneExit() 
{
	for (int i = 0; i < numOfBalls; i++) 
	{
		ballCollision[i]->StopDetectingCollision();
		//particleEmiitters[i]->DeregisterFromScene();
	}

	updateBall.StopUpdating();
	go_Ball.StopDrawingColorLight();
}