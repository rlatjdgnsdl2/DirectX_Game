#pragma once

// Ό³Έν :
class Khaliain
{
public:
	// constrcuter destructer
	Khaliain();
	virtual ~Khaliain();

	// delete Function
	Khaliain(const Khaliain& _Other) = delete;
	Khaliain(Khaliain&& _Other) noexcept = delete;
	Khaliain& operator=(const Khaliain& _Other) = delete;
	Khaliain& operator=(Khaliain&& _Other) noexcept = delete;

protected:

private:

};

