#ifndef SkyBox_h
#define SkyBox_h

#include "../../Math/Matrix/Matrix4F.h"
#include "Model.h"


class Texture;
class ShaderBase;
class ShaderTexture;
struct ID3D11DeviceContext;
struct ID3D11Device;

/// \ingroup GRAPHICOBJS
/// \{

class SkyBox : public Model
{
public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;						// Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(float length, float width, float height, ID3D12GraphicsCommandList4* cmdList);


};
/// \}

#endif SkyBox_h
