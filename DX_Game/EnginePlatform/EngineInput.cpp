#include "PreCompile.h"
#include "EngineInput.h"


void UEngineInput::UEngineKey::KeyCheck(float _DeltaTime)
{
	if (0 != GetAsyncKeyState(Key))
	{
		if (true == IsPress)
		{
			PressTime += _DeltaTime;
		}
		if (true == IsFree)
		{
			IsDown = true;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}
		else if (true == IsDown)
		{
			FreeTime = 0.0f;
			IsDown = false;
			IsPress = true;
			IsFree = false;
			IsUp = false;
		}

	}
	else
	{
		if (true == IsFree)
		{
			FreeTime += _DeltaTime;
		}

		if (true == IsPress)
		{
			IsDown = false;
			IsPress = false;
			IsFree = true;
			IsUp = true;
		}
		else if (true == IsUp)
		{
			PressTime = 0.0f;
			IsDown = false;
			IsPress = false;
			IsFree = true;
			IsUp = false;
		}

	}
}

void UEngineInput::UEngineKey::EventCheck()
{
	if (true == IsDown)
	{
		for (size_t i = 0; i < DownEvents.size(); i++)
		{
			DownEvents[i]();
		}
	}

	if (true == IsPress)
	{
		for (size_t i = 0; i < PressEvents.size(); i++)
		{
			PressEvents[i]();
		}
	}

	if (true == IsFree)
	{
		for (size_t i = 0; i < FreeEvents.size(); i++)
		{
			FreeEvents[i]();
		}
	}

	if (true == IsUp)
	{
		for (size_t i = 0; i < UpEvents.size(); i++)
		{
			UpEvents[i]();
		}
	}
}

UEngineInput& UEngineInput::GetInst()
{
	static UEngineInput Inst = UEngineInput();
	return Inst;
}

UEngineInput::UEngineInput()
{
	Keys.insert({ 'ESC'		, UEngineKey(VK_ESCAPE) });
	Keys.insert({ 'F1'		, UEngineKey(VK_F1) });
	Keys.insert({ 'F2'		, UEngineKey(VK_F2) });
	Keys.insert({ 'F3'		, UEngineKey(VK_F3) });
	Keys.insert({ 'F4'		, UEngineKey(VK_F4) });
	Keys.insert({ 'F5'		, UEngineKey(VK_F5) });
	Keys.insert({ 'F6'		, UEngineKey(VK_F6) });
	Keys.insert({ 'F7'		, UEngineKey(VK_F7) });
	Keys.insert({ 'F8'		, UEngineKey(VK_F8) });
	Keys.insert({ 'F9'		, UEngineKey(VK_F9) });
	Keys.insert({ 'F10'		, UEngineKey(VK_F10) });
	Keys.insert({ 'F11'		, UEngineKey(VK_F11) });
	Keys.insert({ 'F12'		, UEngineKey(VK_F12) });

	Keys.insert({ '`', UEngineKey(VK_OEM_3) });
	Keys.insert({ '1', UEngineKey('1') });
	Keys.insert({ '2', UEngineKey('2') });
	Keys.insert({ '3', UEngineKey('3') });
	Keys.insert({ '4', UEngineKey('4') });
	Keys.insert({ '5', UEngineKey('5') });
	Keys.insert({ '6', UEngineKey('6') });
	Keys.insert({ '7', UEngineKey('7') });
	Keys.insert({ '8', UEngineKey('8') });
	Keys.insert({ '9', UEngineKey('9') });
	Keys.insert({ '0', UEngineKey('0') });
	Keys.insert({ '-', UEngineKey(VK_OEM_MINUS) });
	Keys.insert({ '=', UEngineKey(VK_OEM_PLUS) });

	Keys.insert({ 'BACK', UEngineKey(VK_BACK) });

	Keys.insert({ 'TAB', UEngineKey(VK_TAB) });

	Keys.insert({ 'Q', UEngineKey('Q') });
	Keys.insert({ 'W', UEngineKey('W') });
	Keys.insert({ 'E', UEngineKey('E') });
	Keys.insert({ 'R', UEngineKey('R') });
	Keys.insert({ 'T', UEngineKey('T') });
	Keys.insert({ 'Y', UEngineKey('Y') });
	Keys.insert({ 'U', UEngineKey('U') });
	Keys.insert({ 'I', UEngineKey('I') });
	Keys.insert({ 'O', UEngineKey('O') });
	Keys.insert({ 'P', UEngineKey('P') });

	Keys.insert({ '[', UEngineKey(VK_OEM_4) });
	Keys.insert({ ']', UEngineKey(VK_OEM_6) });
	Keys.insert({ '\\', UEngineKey(VK_OEM_5) });

	Keys.insert({ 'A', UEngineKey('A') });
	Keys.insert({ 'S', UEngineKey('S') });
	Keys.insert({ 'D', UEngineKey('D') });
	Keys.insert({ 'F', UEngineKey('F') });
	Keys.insert({ 'G', UEngineKey('G') });
	Keys.insert({ 'H', UEngineKey('H') });
	Keys.insert({ 'J', UEngineKey('J') });
	Keys.insert({ 'K', UEngineKey('K') });
	Keys.insert({ 'L', UEngineKey('L') });
	Keys.insert({ ';', UEngineKey(VK_OEM_1) });
	Keys.insert({ '\'', UEngineKey(VK_OEM_7) });

	Keys.insert({ 'Z', UEngineKey('Z') });
	Keys.insert({ 'X', UEngineKey('X') });
	Keys.insert({ 'C', UEngineKey('C') });
	Keys.insert({ 'V', UEngineKey('V') });
	Keys.insert({ 'B', UEngineKey('B') });
	Keys.insert({ 'N', UEngineKey('N') });
	Keys.insert({ 'M', UEngineKey('M') });
	Keys.insert({ ',', UEngineKey(VK_OEM_COMMA) });
	Keys.insert({ '.', UEngineKey(VK_OEM_PERIOD) });
	Keys.insert({ '/', UEngineKey(VK_OEM_2) });

	Keys.insert({ VK_LCONTROL, UEngineKey(VK_LCONTROL) });
	Keys.insert({ VK_LSHIFT, UEngineKey(VK_LSHIFT) });
	Keys.insert({ VK_LMENU, UEngineKey(VK_LMENU) });
	Keys.insert({ VK_SPACE		, UEngineKey(VK_SPACE) });

	Keys.insert({ VK_INSERT		, UEngineKey(VK_INSERT) });
	Keys.insert({ VK_DELETE		, UEngineKey(VK_DELETE) });
	Keys.insert({ VK_HOME		, UEngineKey(VK_HOME) });
	Keys.insert({ VK_END		, UEngineKey(VK_END) });
	Keys.insert({ VK_PRIOR		, UEngineKey(VK_HOME) });
	Keys.insert({ VK_NEXT		, UEngineKey(VK_HOME) });



	Keys.insert({ VK_LBUTTON , UEngineKey(VK_LBUTTON) });
	Keys.insert({ VK_RBUTTON , UEngineKey(VK_RBUTTON) });
	Keys.insert({ VK_LEFT , UEngineKey(VK_LEFT) });
	Keys.insert({ VK_RIGHT , UEngineKey(VK_RIGHT) });
	Keys.insert({ VK_UP , UEngineKey(VK_UP) });
	Keys.insert({ VK_DOWN , UEngineKey(VK_DOWN) });

	Keys.insert({ VK_NUMPAD0	, UEngineKey(VK_NUMPAD0) });
	Keys.insert({ VK_NUMPAD1	, UEngineKey(VK_NUMPAD1) });
	Keys.insert({ VK_NUMPAD2	, UEngineKey(VK_NUMPAD2) });
	Keys.insert({ VK_NUMPAD3	, UEngineKey(VK_NUMPAD3) });
	Keys.insert({ VK_NUMPAD4	, UEngineKey(VK_NUMPAD4) });
	Keys.insert({ VK_NUMPAD5	, UEngineKey(VK_NUMPAD5) });
	Keys.insert({ VK_NUMPAD6	, UEngineKey(VK_NUMPAD6) });
	Keys.insert({ VK_NUMPAD7	, UEngineKey(VK_NUMPAD7) });
	Keys.insert({ VK_NUMPAD8	, UEngineKey(VK_NUMPAD8) });
	Keys.insert({ VK_NUMPAD9	, UEngineKey(VK_NUMPAD9) });
	Keys.insert({ VK_MULTIPLY	, UEngineKey(VK_MULTIPLY) });
	Keys.insert({ VK_ADD		, UEngineKey(VK_ADD) });
	Keys.insert({ VK_SEPARATOR	, UEngineKey(VK_SEPARATOR) });
	Keys.insert({ VK_SUBTRACT	, UEngineKey(VK_SUBTRACT) });
	Keys.insert({ VK_DECIMAL	, UEngineKey(VK_DECIMAL) });
	Keys.insert({ VK_DIVIDE	, UEngineKey(VK_DIVIDE) });

}

void UEngineInput::EventCheck(float _DeltaTime)
{
	std::map<int, UEngineKey>::iterator StartIter = GetInst().Keys.begin();
	std::map<int, UEngineKey>::iterator EndIter = GetInst().Keys.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UEngineKey& CurKey = StartIter->second;
		CurKey.EventCheck();
	}
}

void UEngineInput::KeyCheck(float _DeltaTime)
{
	std::map<int, UEngineKey>::iterator StartIter = GetInst().Keys.begin();
	std::map<int, UEngineKey>::iterator EndIter = GetInst().Keys.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		UEngineKey& CurKey = StartIter->second;
		CurKey.KeyCheck(_DeltaTime);
	}

	EventCheck(_DeltaTime);
}

UEngineInput::~UEngineInput()
{
}

void UEngineInput::BindAction(int _KeyIndex, KeyEvent _EventType, std::function<void() > _Function)
{
	if (false == Keys.contains(_KeyIndex))
	{
		MSGASSERT("������ ��ϵ��� ���� Ű�� �����մϴ�.");
		return;
	}

	switch (_EventType)
	{
	case KeyEvent::Down:
		Keys[_KeyIndex].DownEvents.push_back(_Function);
		break;
	case KeyEvent::Press:
		Keys[_KeyIndex].PressEvents.push_back(_Function);
		break;
	case KeyEvent::Free:
		Keys[_KeyIndex].FreeEvents.push_back(_Function);
		break;
	case KeyEvent::Up:
		Keys[_KeyIndex].UpEvents.push_back(_Function);
		break;
	default:
		break;
	}


}