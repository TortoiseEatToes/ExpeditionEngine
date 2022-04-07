#ifndef	GraphicObjectAttorney_h
#define	GraphicObjectAttorney_h

#include "GraphicsObject.h"

class GraphicsObjectAttorney 
{
public:
	struct GraphicsSceneControl
	{
	private:
		friend class GraphicsScene;

		static void RegisterColor(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->RegisterColor(pGraphicsObjectDataManager);
		}

		static void DeregisterColor(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->DeregisterColor(pGraphicsObjectDataManager);
		}

		static void RegisterColorLight(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->RegisterColorLight(pGraphicsObjectDataManager);
		}

		static void DeregisterColorLight(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->DeregisterColorLight(pGraphicsObjectDataManager);
		}

		static void RegisterTexture(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->RegisterTexture(pGraphicsObjectDataManager);
		}

		static void DeregisterTexture(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->DeregisterTexture(pGraphicsObjectDataManager);
		}

		static void RegisterTextureLight(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->RegisterTextureLight(pGraphicsObjectDataManager);
		}

		static void DeregisterTextureLight(GraphicsObject* pGO, GO_Data_Manager* pGraphicsObjectDataManager)
		{
			pGO->DeregisterTextureLight(pGraphicsObjectDataManager);
		}

		static void SetRegistrationState(RegistrationState state, GraphicsObject* pGO)
		{
			pGO->regState = state;
		}
	};
};

#endif 	GraphicObjectAttorney_h
