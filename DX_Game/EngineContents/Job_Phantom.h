#pragma once
#include "Job.h"

//	����:
class UJob_Phantom : public UJob
{
public:
	UJob_Phantom();
	virtual ~UJob_Phantom();
	UJob_Phantom(const UJob_Phantom& _Other) = delete;
	UJob_Phantom(UJob_Phantom&& _Other) noexcept = delete;
	UJob_Phantom& operator=(const UJob_Phantom& _Other) = delete;
	UJob_Phantom& operator=(UJob_Phantom&& _Other) noexcept = delete;

protected:

private:
	
	


};

