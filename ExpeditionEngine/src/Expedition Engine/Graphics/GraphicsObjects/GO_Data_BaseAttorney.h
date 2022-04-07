#pragma once
#include "GO_Data_Base.h"

class GO_Data_BaseAttorney
{
public:
	struct ManagerControl
	{
	private:
		friend class GO_Data_Color_Manager;
		friend class GO_Data_ColorLight_Manager;
		friend class GO_Data_Texture_Manager;
		friend class GO_Data_TextureLight_Manager;
		friend class GO_Data_Manager;

		static void Initialize_12(GO_Data_Base& pGO, GraphicsResourcesManager* pGraphicsResourcesManager, Model* mod, int numberOfInsts)
		{
			pGO.Initialize_12(pGraphicsResourcesManager, mod, numberOfInsts);
		}

		static void Initialize_12(GO_Data_Base& pGO, GraphicsResourcesManager* pGraphicsResourcesManager, TerrainModel* mod)
		{
			pGO.Initialize_12(pGraphicsResourcesManager, mod);
		}

		static void Sanitize_12(GO_Data_Base& pGO, GraphicsResourcesManager* pGraphicsResourcesManager)
		{
			pGO.Sanitize_12(pGraphicsResourcesManager);
		}

		static void Render_12(GO_Data_Base& pGO, ID3D12GraphicsCommandList4* cmdList)
		{
			pGO.Render_12(cmdList);
		}

		static void PrepareForRender(GO_Data_Base& pGO, ID3D12GraphicsCommandList4* cmdList)
		{
			pGO.PrepareToRender(cmdList);
		}
	};
};