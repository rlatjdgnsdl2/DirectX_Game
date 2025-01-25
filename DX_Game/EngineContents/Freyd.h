#pragma once

// Ό³Έν :
class Freyd
{
public:
	// constrcuter destructer
	Freyd();
	virtual ~Freyd();

	// delete Function
	Freyd(const Freyd& _Other) = delete;
	Freyd(Freyd&& _Other) noexcept = delete;
	Freyd& operator=(const Freyd& _Other) = delete;
	Freyd& operator=(Freyd&& _Other) noexcept = delete;

protected:

private:

};

