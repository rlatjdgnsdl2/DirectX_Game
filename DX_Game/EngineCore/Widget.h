#pragma once
#include "TransformObject.h"

// ���� : �������� ���Ѵٰ� �����ϰ�
class UWidget : public UTransformObject
{
public:
	// constrcuter destructer
	UWidget();
	~UWidget();

	// delete Function
	UWidget(const UWidget& _Other) = delete;
	UWidget(UWidget&& _Other) noexcept = delete;
	UWidget& operator=(const UWidget& _Other) = delete;
	UWidget& operator=(UWidget&& _Other) noexcept = delete;

};

