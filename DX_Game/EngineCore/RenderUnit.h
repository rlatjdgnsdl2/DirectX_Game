#pragma once

//	Ό³Έν:
class URenderUnit
{
public:
	URenderUnit();
	virtual ~URenderUnit();
	URenderUnit(const URenderUnit& _Other) = delete;
	URenderUnit(URenderUnit&& _Other) noexcept = delete;
	URenderUnit& operator=(const URenderUnit& _Other) = delete;
	URenderUnit& operator=(URenderUnit&& _Other) noexcept = delete;

protected:

private:

};

