#pragma once
#include "Job.h"

//	Ό³Έν:
class APhantom : public UJobComponent
{
public:
	APhantom();
	virtual ~APhantom();
	APhantom(const APhantom& _Other) = delete;
	APhantom(APhantom&& _Other) noexcept = delete;
	APhantom& operator=(const APhantom& _Other) = delete;
	APhantom& operator=(APhantom&& _Other) noexcept = delete;

protected:

private:
	
	


};

