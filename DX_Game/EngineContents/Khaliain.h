#pragma once

// Ό³Έν :
class AKhaliain
{
public:
	// constrcuter destructer
	AKhaliain();
	virtual ~AKhaliain();

	// delete Function
	AKhaliain(const AKhaliain& _Other) = delete;
	AKhaliain(AKhaliain&& _Other) noexcept = delete;
	AKhaliain& operator=(const AKhaliain& _Other) = delete;
	AKhaliain& operator=(AKhaliain&& _Other) noexcept = delete;

protected:

private:

};

