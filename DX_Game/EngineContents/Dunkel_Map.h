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
		return BackRenderer.get();
	}



protected:

private:
	std::map<std::string, std::shared_ptr<class UCollision>> EndArea;
	std::shared_ptr<class USpriteRenderer> FootHoldRenderer;

	std::shared_ptr<class USpriteRenderer> BackRenderer;
	std::list<std::shared_ptr<class USpriteRenderer>> ObjectRenderers;

	

};

