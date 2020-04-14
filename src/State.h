#pragma once
#ifndef __STATE__
#define __STATE__
#include "ActionState.h"

/* abstract class */
class State
{
public:
	State(ActionState action_state = NO_ACTION_STATE);
	virtual ~State() = 0;

	// function pointer definition for the Action Function
	typedef void(*Action)();

	// getters and setters
	void setActionState(ActionState state);
	void setAction(Action action);
	void performAction() const;

	void setUtility(float utility);
	float getUtility() const;
private:
	ActionState m_actionState;
	Action m_action; // reference to the action callback

	float m_utility;
};
#endif /* defined (__STATE__) */