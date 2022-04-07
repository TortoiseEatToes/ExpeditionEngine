#ifndef ACTIONDEREGISTERBASE_H
#define ACTIONDEREGISTERBASE_H


#include "../GraphicsObjectRegistrationActionStrategy.h"

class ActionDeregisterBase : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionDeregisterBase() = default;
	ActionDeregisterBase(ActionDeregisterBase&& other) = delete;
	ActionDeregisterBase(const ActionDeregisterBase& other) = delete;
	ActionDeregisterBase& operator= (ActionDeregisterBase&& other) = delete;
	ActionDeregisterBase& operator= (const ActionDeregisterBase& other) = delete;
	~ActionDeregisterBase() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

#endif //!ACTIONDEREGISTERBASE_H