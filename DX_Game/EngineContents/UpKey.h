#pragma once
#include "PlayerFunction.h"

//	Ό³Έν:
class AUpKey : public APlayerFunction
{
public:
	AUpKey();
	virtual ~AUpKey();
	AUpKey(const AUpKey& _Other) = delete;
	AUpKey(AUpKey&& _Other) noexcept = delete;
	AUpKey& operator=(const AUpKey& _Other) = delete;
	AUpKey& operator=(AUpKey&& _Other) noexcept = delete;

protected:

private:

};

