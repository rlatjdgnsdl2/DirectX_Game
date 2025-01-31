#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class ADunkel_Map : public AActor
{
public:
	ADunkel_Map();
	virtual ~ADunkel_Map();
	ADunkel_Map(const ADunkel_Map& _Other) = delete;
	ADunkel_Map(ADunkel_Map&& _Other) noexcept = delete;
	ADunkel_Map& operator=(const ADunkel_Map& _Other) = delete;
	ADunkel_Map& operator=(ADunkel_Map&& _Other) noexcept = delete;

	class USpriteRenderer* GetBackRenderer()
	{
		return BackRenderer;
	}



protected:

private:
	std::map<std::string, class UMyCollision*> EndArea;
	class USpriteRenderer* FootHoldRenderer;
	class USpriteRenderer* BackRenderer;

	std::list<class USpriteRenderer*> ObjectRenderers;

	

};

