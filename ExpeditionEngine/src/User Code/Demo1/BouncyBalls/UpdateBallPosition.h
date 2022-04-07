#pragma once


#include "../../../Expedition Engine/Scene Components/Update/UpdateComponent.h"
#include "..//..//..//Expedition Engine/Math/Vector/Vector4F.h"
#include "..//..//..//Expedition Engine/Math/Matrix/Matrix4F.h"
#include "..//..//..//Expedition Engine/Graphics/GraphicsObjects/GraphicsObject.h"
#include "..//..//..//Expedition Engine/Math/MathTools.h"
#include "../Collision/BallCollision.h"
#include "../../../Expedition Engine/Scene Components/Particle Emitter/ParticleEmitter.h"
#include "../../../Expedition Engine/Graphics/Terrain/TerrainObjectManager.h"
#include "../../../Expedition Engine/Graphics/Terrain/TerrainModel.h"

class UpdateBallPosition : public UpdateComponent 
{
public:

	GraphicsObject* go_Ball;
	Vector4F** velocityVects;
	Matrix4F** worldMatrices;
	BallCollision** ballCollision;
	TerrainModel* terrain;
	ParticleEmitter** particleEmitters;
	int numOfBalls;

private:

	void OnUpdate() override{


		terrain = TerrainObjectManager::Get(TerrainName::TestTerrain);

		for (int i = 0; i < numOfBalls; i++) 
		{
			(*worldMatrices)[i] *= Matrix4F(TRANS, (*velocityVects)[i]);

			(*velocityVects)[i].Y() -= .09f;


			(*worldMatrices)[i].V3() = MathTools::Clamp((*worldMatrices)[i].V3(), Vector4F(-100,-100,-100), Vector4F(100, 100, 100));



			particleEmitters[i]->SetParticlePosition((*worldMatrices)[i].V3());

			//particleEmitters[i]->SetParticleVelocity(-(*velocityVects)[i].X() - 1.0f, -(*velocityVects)[i].X() + 1.0f, -(*velocityVects)[i].Y() - 1.0f, -(*velocityVects)[i].Y() + 1.0f, -(*velocityVects)[i].Z() - 1.0f,
			//	-(*velocityVects)[i].Z() + 1.0f);

			particleEmitters[i]->SetParticleVelocity(((*velocityVects)[i]) * (-1.0f), 20.0f);


			//particleEmitters[i]->SetPosition((*worldMatrices)[i].V3());

			float height = terrain->BarycentrifyHeight((*worldMatrices)[i].V3());

			if ((*worldMatrices)[i].V3().Y() < height)
			{
				(*worldMatrices)[i].V3().Y() = height;

				Vector4F norm = terrain->BarycentrifyNormal((*worldMatrices)[i].V3());

				(*velocityVects)[i] =  norm * 3.0f;
				(*velocityVects)[i].W() = 1;
			}

			go_Ball->SetWorld((*worldMatrices)[i], i);
			ballCollision[i]->SetWorld((*worldMatrices)[i]);
		}


	}

};
