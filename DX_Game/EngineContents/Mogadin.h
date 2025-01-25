#pragma once

// Ό³Έν :
class Mogadin
{
public:
	// constrcuter destructer
	Mogadin();
	virtual ~Mogadin();

	// delete Function
	Mogadin(const Mogadin& _Other) = delete;
	Mogadin(Mogadin&& _Other) noexcept = delete;
	Mogadin& operator=(const Mogadin& _Other) = delete;
	Mogadin& operator=(Mogadin&& _Other) noexcept = delete;

protected:

private:

};

