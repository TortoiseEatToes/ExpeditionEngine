#ifndef SpriteModel_h
#define SpriteModel_h

#include "../../Math/Matrix/Matrix4F.h"
#include "Model.h"

class Texture;
class ShaderBase;

/// \ingroup GRAPHICOBJS
/// \{

class SpriteModel : public Model
{
public:
	SpriteModel(const SpriteModel&) = delete;				// Copy constructor
	SpriteModel(Model&&) = delete;						// Move constructor
	SpriteModel& operator=(const SpriteModel&) & = delete;  // Copy assignment operator
	SpriteModel& operator=(SpriteModel&&) & = delete;       // Move assignment operator
	~SpriteModel();

	SpriteModel(float length, float width, ID3D12GraphicsCommandList4* cmdList);
};
/// \}

#endif //!SpriteModel_h
