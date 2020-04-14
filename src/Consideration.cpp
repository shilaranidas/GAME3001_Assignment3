#include "Consideration.h"

Consideration::Consideration()
= default;

bool Consideration::And(Consideration* lhs, Consideration* rhs)
{
	return (lhs->test() && rhs->test());
}

bool Consideration::Or(Consideration* lhs, Consideration* rhs)
{
	return (lhs->test() || rhs->test());
}
