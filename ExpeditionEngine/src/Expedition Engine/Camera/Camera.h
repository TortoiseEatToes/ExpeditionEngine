#ifndef CAMERA_H
#define CAMERA_H

#include "../Containers/PooledResourceIterator.h"

#include "../../Expedition Resources/SceneSettings.h"

class CameraDataDoubleBuffer;

class TerrainModel;
class Vector4F;
class Matrix4F;
class CameraDataManager;

class Camera
{

public:
	enum class Type
	{
		PERSPECTIVE_3D,
		ORTHOGRAPHIC_2D
	};

	Camera() = delete;
	Camera(const Type& type, const SceneName& sceneToExistIn);
	Camera& operator= (const Camera& other) = delete;
	~Camera();

	void SetType(const Type& type);

	// Setup on single camera
	void SetPerspective(const float& fieldOfView_Degs, const float& initAspectRatio, const float& initNearDist, const float& initFarDist);
	void SetOrthographic(const float& initXmin, const float& initXmax, const float& initYmin, const float& initYmax, const float& initZmin, const float& initZmax);
	void SetOrientAndPosition(const Vector4F &up_vect, const Vector4F &inLookAt_pt, const Vector4F &pos_pt);

	// Get the matrices for rendering
	const Matrix4F& GetViewMatrix() const;
	const Matrix4F& GetProjMatrix() const;

	// accessors
	void GetPosition(Vector4F &outPos) const;
	const Vector4F& GetPosition() const;
	//void GetDir(Vector4F &outDir) const;
	const Vector4F& GetDirection() const;
	void GetUp(Vector4F &outUp) const;
	//void GetLookAt(Vector4F &outLookAt) const;
	//void GetRight(Vector4F &outRight) const;
	const Vector4F& GetRight() const;

	void TranslateLeftRight(const float& delta);
	void TranslateFwdBack(const float& delta);
	void TiltUpDown(const float& ang);
	void TurnLeftRight(const float& ang);

	void AlignHeightToTerrain(TerrainModel const * terrain, const float& offsetFromTerrain);

	void Update();

private:
	friend class CameraAttorney;

	PooledResourceIterator<CameraDataDoubleBuffer>& GetIterator();

	PooledResourceIterator<CameraDataDoubleBuffer> iterator;
	SceneName registeredScene;
};

#endif