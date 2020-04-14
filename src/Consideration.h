#pragma once
#ifndef __CONSIDERATION__
#define __CONSIDERATION__

/* abstract class */
class Consideration
{
public:
	Consideration();
	virtual ~Consideration() = 0;

	static bool And(Consideration* lhs, Consideration* rhs);
	static bool Or(Consideration* lhs, Consideration* rhs);

	// abstract test function
	virtual bool test() = 0;
private:
	
};


#endif /* defined (__CONSIDERATION__) */
