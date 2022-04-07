#pragma once

#include "GraphicsScene.h"

class GraphicsSceneAttorney {
public:
	class ManagerControls 
	{
	private:
		friend class GraphicsSceneManager;
		friend class ParticleEmitter;

		static void InsertCommand(GraphicsScene* pScene, GraphicsSceneCommand* pCommand) { pScene->InsertCommand(pCommand); }
		static void Render(GraphicsScene* pGS) { pGS->Render(); }
		static void RenderParticles(GraphicsScene* pGS) { pGS->RenderParticles(); }
	};

	class ActionControls 
	{
	private:
		friend class ActionRegisterColor;
		friend class ActionDeregisterColor;

		friend class ActionRegisterColorLight;
		friend class ActionDeregisterColorLight;

		friend class ActionRegisterTexture;
		friend class ActionDeregisterTexture;

		friend class ActionRegisterTextureLight;
		friend class ActionDeregisterTextureLight;

		static void RegisterGraphicsObjectColor(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->RegisterGraphicsObjectColor(pGO); }
		static void DeregisterGraphicsObjectColor(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->DeregisterGraphicsObjectColor(pGO); }

		static void RegisterGraphicsObjectColorLight(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->RegisterGraphicsObjectColorLight(pGO); }
		static void DeregisterGraphicsObjectColorLight(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->DeregisterGraphicsObjectColorLight(pGO); }

		static void RegisterGraphicsObjectTexture(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->RegisterGraphicsObjectTexture(pGO); }
		static void DeregisterGraphicsObjectTexture(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->DeregisterGraphicsObjectTexture(pGO); }

		static void RegisterGraphicsObjectTextureLight(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->RegisterGraphicsObjectTextureLight(pGO); }
		static void DeregisterGraphicsObjectTextureLight(GraphicsObject* pGO, GraphicsScene* pGS) { pGS->DeregisterGraphicsObjectTextureLight(pGO); }
	};

	struct GraphicsObjectChildControl
	{
	private:
		friend class GraphicsObject;
		friend class GraphicsObject_ColorLight;
		friend class GraphicsObject_Sprite;
		friend class GraphicsObject_Texture;
		friend class GraphicsObject_TextureLight;

		static GO_Data_Manager& GetGraphicsObjectDataManager(GraphicsScene* pGraphicsScene)
		{
			return pGraphicsScene->GetGraphicsObjectDataManager();
		}
	};



};