#pragma once

// Ό³Έν :
class UPlayerDataManager 
{
public:
	// constrcuter destructer
	UPlayerDataManager();
	virtual ~UPlayerDataManager();

	// delete Function
	UPlayerDataManager(const UPlayerDataManager& _Other) = delete;
	UPlayerDataManager(UPlayerDataManager&& _Other) noexcept = delete;
	UPlayerDataManager& operator=(const UPlayerDataManager& _Other) = delete;
	UPlayerDataManager& operator=(UPlayerDataManager&& _Other) noexcept = delete;

protected:

private:

};

