#include "State.h"

State::State(const ActionState action_state)
	:m_actionState(action_state), m_action(nullptr), m_utility(0.0f)
{
}


void State::setActionState(const ActionState state)
{
	m_actionState = state;
}

void State::setAction(const Action action)
{
	m_action = action;
}

void State::performAction() const
{
	m_action();
}

void State::setUtility(const float utility)
{
	m_utility = utility;
}

float State::getUtility() const
{
	return m_utility;
}
