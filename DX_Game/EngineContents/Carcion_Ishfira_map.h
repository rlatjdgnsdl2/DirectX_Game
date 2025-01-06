#pragma once
#include <EngineCore/Actor.h>

//	Ό³Έν:
class ACarcion_Ishfira_Map : public AActor
{
public:
	ACarcion_Ishfira_Map();
	virtual ~ACarcion_Ishfira_Map();
	ACarcion_Ishfira_Map(const ACarcion_Ishfira_Map& _Other) = delete;
	ACarcion_Ishfira_Map(ACarcion_Ishfira_Map&& _Other) noexcept = delete;
	ACarcion_Ishfira_Map& operator=(const ACarcion_Ishfira_Map& _Other) = delete;
	ACarcion_Ishfira_Map& operator=(ACarcion_Ishfira_Map&& _Other) noexcept = delete;

protected:

private:
	//std::shared_ptr<class USpriteRenderer> BackRenderer;


};

