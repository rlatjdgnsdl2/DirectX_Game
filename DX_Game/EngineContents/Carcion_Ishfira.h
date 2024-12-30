#pragma once
#include <EngineCore/GameMode.h>

//	Ό³Έν:
class ACarcion_Ishfira :public AGameMode
{
public:
	ACarcion_Ishfira();
	virtual ~ACarcion_Ishfira();
	ACarcion_Ishfira(const ACarcion_Ishfira& _Other) = delete;
	ACarcion_Ishfira(ACarcion_Ishfira&& _Other) noexcept = delete;
	ACarcion_Ishfira& operator=(const ACarcion_Ishfira& _Other) = delete;
	ACarcion_Ishfira& operator=(ACarcion_Ishfira&& _Other) noexcept = delete;

protected:

private:
	std::shared_ptr<class ACarcion_Ishfira_Map> Carcion_Ishfira_Map = nullptr;
};

