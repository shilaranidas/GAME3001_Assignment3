#include "FloatConsideration.h"

//FloatConsideration::FloatConsideration(const float min_value, const float max_value, const float test_value):m_minValue(min_value), m_maxValue(max_value), m_testValue(test_value){}
//
//FloatConsideration::~FloatConsideration()
//= default;

void FloatConsideration::setTestValue(const float value)
{
	m_testValue = value;
}

void FloatConsideration::setMinValue(const float value)
{
	m_minValue = value;
}

void FloatConsideration::setMaxValue(const float value)
{
	m_maxValue = value;
}

bool FloatConsideration::test()
{
	return ((m_minValue <= m_testValue) && (m_testValue <= m_maxValue));
}
