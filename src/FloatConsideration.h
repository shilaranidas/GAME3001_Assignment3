#pragma once
#ifndef __FLOAT_CONSIDERATION__
#define __FLOAT_CONSIDERATION__
#include "Consideration.h"

class FloatConsideration : public Consideration
{
public:
	/*FloatConsideration(float min_value = 0, float max_value = 0, float test_value = 0);
	~FloatConsideration();*/

	// getters and setters
	void setTestValue(float value);
	void setMinValue(float value);
	void setMaxValue(float value);


	virtual bool test() override;
private:
	float m_minValue;
	float m_maxValue;
	float m_testValue;
};
#endif /* defined (__FLOAT_CONSIDERATION__) */
