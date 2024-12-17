#include "PreCompile.h"
#include "Renderer.h"

URenderer::URenderer()
{
}

URenderer::~URenderer()
{
}

void URenderer::SetOrder(int _Order)
{
	int PrevOrder = GetOrder();
	// 100���� �Ǿ���?
	UObject::SetOrder(_Order);

	ULevel* Level = GetActor()->GetWorld();

	// std::shared_ptr<URenderer> Render(this);
	// std::enable_shared_from_this<UObject> ��ӹ��� Ŭ������ �ڱ��ڽ��� this
	// std::shared_ptr�� ������� this�� ����ϰ� ������ ȣ���ϴ� �Լ�.
	// std::shared_ptr<UObject> ObjectPtr = UObject::shared_from_this();
	// dynmaic_cast�� ����ϴ� ����� ���� ���̴�. 
	// dynamic_cast <= �� ������ �����͸� ��ȯ��Ű�� �༮���� std::shared_ptr
	// std::shared_ptr<int> NewInt = std::make_shared<int>();
	// std::shared_ptr<URenderer> RendererPtr = std::dynamic_pointer_cast<URenderer>(ObjectPtr);
	std::shared_ptr<URenderer> RendererPtr = GetThis<URenderer>();

	Level->ChangeRenderGroup(PrevOrder, RendererPtr);
}

ENGINEAPI void URenderer::BeginPlay()
{
	SetOrder(0);
}

void URenderer::Render(float _DeltaTime)
{
	// ������ ����������

}