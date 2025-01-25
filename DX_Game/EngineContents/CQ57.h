#pragma once
#include "Monster.h"

// Ό³Έν :
class ACQ57 : public AMonster
{
public:
	// constrcuter destructer
	ACQ57();
	virtual ~ACQ57();

	// delete Function
	ACQ57(const ACQ57& _Other) = delete;
	ACQ57(ACQ57&& _Other) noexcept = delete;
	ACQ57& operator=(const ACQ57& _Other) = delete;
	ACQ57& operator=(ACQ57&& _Other) noexcept = delete;

protected:

private:
	//void Start

};

