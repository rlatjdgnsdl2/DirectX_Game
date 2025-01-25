#pragma once

// Ό³Έν :
class AMogadin
{
public:
	// constrcuter destructer
	AMogadin();
	virtual ~AMogadin();

	// delete Function
	AMogadin(const AMogadin& _Other) = delete;
	AMogadin(AMogadin&& _Other) noexcept = delete;
	AMogadin& operator=(const AMogadin& _Other) = delete;
	AMogadin& operator=(AMogadin&& _Other) noexcept = delete;

protected:

private:

};

