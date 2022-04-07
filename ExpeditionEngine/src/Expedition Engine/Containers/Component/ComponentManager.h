#pragma once

#include "../List.h"
#include "ComponentChunk.h"

class Component;
//template <typename Component>
class ComponentManager
{
public:
	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(const Iterator& other) = delete;
		Iterator& operator= (const Iterator& other) = delete;
		~Iterator() = default;

		Component& GetComponent()
		{
			return pChunk->GetComponent(*pIndex);
		}

	private:
		friend class ComponentManager;

		void SetChunk(ComponentChunk<Component>& pComponentChunk)
		{
			pChunk = &pComponentChunk;
		}

		int*& GetIndex()
		{
			return pIndex;
		}

		void Release()
		{
			pChunk->Release(*pIndex);
		}

		ComponentChunk<Component>* pChunk = nullptr;
		int* pIndex = nullptr;
	};

	
	ComponentManager() = delete;
	ComponentManager(const int& size)
	{
		chunkSize = size;
	}
	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator= (const ComponentManager&) = delete;
	~ComponentManager()
	{
		while (listChunks.GetSize() > 0)
		{
			delete &listChunks.PopFront();
		}
	}

	/// <summary>Acquire a component.  The iterator will get a point to the component.</summary>
	void Acquire(Iterator& outIterator)
	{
		bool searching = true;

		listChunks.SetFront(iterator);
		while (searching && !iterator.IsOutOfNodes())
		{
			if (iterator.GetCurrentObject().Acquire(outIterator.GetIndex()) > 0)
			{
				searching = false;
			}
			else
			{
				++iterator;
			}
		}

		if (searching)
		{
			ComponentChunk<Component>* pChunk = new ComponentChunk<Component>(chunkSize);
			pChunk->Acquire(outIterator.GetIndex());
			listChunks.PushBack(*pChunk);
		}
	}

	/// <summary>Release the resouce stored in this iterator.</summary>
	void Release(Iterator& outIterator)
	{
		outIterator.Release();
	}

	/// <summary>Process all components on all chunks.</summary>
	void Process()
	{
		listChunks.SetFront(iterator);
		while (!iterator.IsOutOfNodes())
		{
			iterator.GetCurrentObject().Process();
			++iterator;
		}
	}

private:
	List<ComponentChunk<Component>*> listChunks;
	List<ComponentChunk<Component>*>::Iterator iterator;
	int chunkSize = -1;
};