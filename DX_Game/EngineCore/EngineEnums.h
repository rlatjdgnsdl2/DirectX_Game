#pragma once

typedef __int8 int8;


enum class EProjectionType : int8
{
	Perspective,
	Orthographic,
};

// 1����Ʈ ���� �� ���̴��� ����� ������ �Ʒ��� ���� �ϸ� �˴ϴ�.
enum class EShaderType : int8
{
	VS, // ���ؽ�
	HS, // 
	DS,
	GS,
	PS,
	CS,
	MAX
};
