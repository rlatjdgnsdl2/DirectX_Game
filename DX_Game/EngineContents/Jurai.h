#pragma once

// Ό³Έν :
class Jurai
{
public:
	// constrcuter destructer
	Jurai();
	virtual ~Jurai();

	// delete Function
	Jurai(const Jurai& _Other) = delete;
	Jurai(Jurai&& _Other) noexcept = delete;
	Jurai& operator=(const Jurai& _Other) = delete;
	Jurai& operator=(Jurai&& _Other) noexcept = delete;

protected:

private:

};

