#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class AMoonBridge_WhiteSpear_Map : public AActor
{
public:
	AMoonBridge_WhiteSpear_Map();
	virtual ~AMoonBridge_WhiteSpear_Map();
	AMoonBridge_WhiteSpear_Map(const AMoonBridge_WhiteSpear_Map& _Other) = delete;
	AMoonBridge_WhiteSpear_Map(AMoonBridge_WhiteSpear_Map&& _Other) noexcept = delete;
	AMoonBridge_WhiteSpear_Map& operator=(const AMoonBridge_WhiteSpear_Map& _Other) = delete;
	AMoonBridge_WhiteSpear_Map& operator=(AMoonBridge_WhiteSpear_Map&& _Other) noexcept = delete;

	virtual void BeginPlay() override;

protected:

private:
	std::map<std::string, std::shared_ptr<class UCollision>> EndArea;
	std::list<std::shared_ptr<class UCollision>> FootHoldCollisions;
	std::map<int, std::shared_ptr<class USpriteRenderer>> FootHoldRenderers;

	std::shared_ptr<class USpriteRenderer> BackRenderer;



};

