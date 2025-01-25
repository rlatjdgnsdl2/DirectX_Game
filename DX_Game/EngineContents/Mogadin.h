#pragma once
#include "Monster.h"
// Ό³Έν :
class AMogadin : public AMonster

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

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:
	int PrevIndex = 0;
	int CurIndex = 0;


	void StartSlash();
	void UpdateSlash(float _DeltaTime);
	void Slash(class UCollision* _Left, class UCollision* _Right);

	void StartChain();
	void UpdateChain(float _DeltaTime);


};

