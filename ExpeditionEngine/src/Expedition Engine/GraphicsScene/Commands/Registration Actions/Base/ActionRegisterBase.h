#ifndef ACTIONREGISTERBASE_H
#define ACTIONREGISTERBASE_H


#include "../GraphicsObjectRegistrationActionStrategy.h"

class ActionRegisterBase : public GraphicsObjectRegistrationActionStrategy
{
public:
	ActionRegisterBase() = default;
	ActionRegisterBase(ActionRegisterBase&& other) = delete;
	ActionRegisterBase(const ActionRegisterBase& other) = delete;
	ActionRegisterBase& operator= (ActionRegisterBase&& other) = delete;
	ActionRegisterBase& operator= (const ActionRegisterBase& other) = delete;
	~ActionRegisterBase() = default;

	void Execute(GraphicsScene* pGraphicsScene, GraphicsObject* pGraphicsObject) override;
};

#endif //!ACTIONREGISTERBASE_H