#include "PreCompile.h"
#include "PlayerInput.h"


PlayerInput::PlayerInput()
{
	KeySetting.insert({ 'ESC',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F1',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F2',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F3',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F4',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F5',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F6',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F7',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F8',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F9',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F10',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F11',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F12',
		[]()
		{

		}
		});

	KeySetting.insert({ '`',
		[]()
		{

		}
		});
	KeySetting.insert({ '1',
		[]()
		{

		}
		});
	KeySetting.insert({ '2',
		[]()
		{

		}
		});
	KeySetting.insert({ '3',
		[]()
		{

		}
		});
	KeySetting.insert({ '4',
		[]()
		{

		}
		});
	KeySetting.insert({ '5',
		[]()
		{

		}
		});
	KeySetting.insert({ '6',
		[]()
		{

		}
		});
	KeySetting.insert({ '7',
		[]()
		{

		}
		});
	KeySetting.insert({ '8',
		[]()
		{

		}
		});
	KeySetting.insert({ '9',
		[]()
		{

		}
		});
	KeySetting.insert({ '0',
		[]()
		{

		}
		});
	KeySetting.insert({ '-',
		[]()
		{

		}
		});
	KeySetting.insert({ '=',
		[]()
		{

		}
		});

	KeySetting.insert({ 'BACK',
		[]()
		{

		}
		});

	KeySetting.insert({ 'TAB',
		[]()
		{

		}
		});

	KeySetting.insert({ 'Q',
		[]()
		{

		}
		});
	KeySetting.insert({ 'W',
		[]()
		{

		}
		});
	KeySetting.insert({ 'E',
		[]()
		{

		}
		});
	KeySetting.insert({ 'R',
		[]()
		{

		}
		});
	KeySetting.insert({ 'T',
		[]()
		{

		}
		});
	KeySetting.insert({ 'Y',
		[]()
		{

		}
		});
	KeySetting.insert({ 'U',
		[]()
		{

		}
		});
	KeySetting.insert({ 'I',
		[]()
		{

		}
		});
	KeySetting.insert({ 'O',
		[]()
		{

		}
		});
	KeySetting.insert({ 'P',
		[]()
		{

		}
		});

	KeySetting.insert({ '[',
		[]()
		{

		}
		});
	KeySetting.insert({ ']',
		[]()
		{

		}
		});
	KeySetting.insert({ '\\',
		[]()
		{

		}
		});

	KeySetting.insert({ 'A',
		[]()
		{

		}
		});
	KeySetting.insert({ 'S',
		[]()
		{

		}
		});
	KeySetting.insert({ 'D',
		[]()
		{

		}
		});
	KeySetting.insert({ 'F',
		[]()
		{

		}
		});
	KeySetting.insert({ 'G',
		[]()
		{

		}
		});
	KeySetting.insert({ 'H',
		[]()
		{

		}
		});
	KeySetting.insert({ 'J',
		[]()
		{

		}
		});
	KeySetting.insert({ 'K',
		[]()
		{

		}
		});
	KeySetting.insert({ 'L',
		[]()
		{

		}
		});
	KeySetting.insert({ ';',
		[]()
		{

		}
		});
	KeySetting.insert({ '\'',
		[]()
		{

		}
		});

	KeySetting.insert({ 'Z',
		[]()
		{

		}
		});
	KeySetting.insert({ 'X',
		[]()
		{

		}
		});
	KeySetting.insert({ 'C',
		[]()
		{

		}
		});
	KeySetting.insert({ 'V',
		[]()
		{

		}
		});
	KeySetting.insert({ 'B',
		[]()
		{

		}
		});
	KeySetting.insert({ 'N',
		[]()
		{

		}
		});
	KeySetting.insert({ 'M',
		[]()
		{

		}
		});
	KeySetting.insert({ ',',
		[]()
		{

		}
		});
	KeySetting.insert({ '.',
		[]()
		{

		}
		});
	KeySetting.insert({ '/',
		[]()
		{

		}
		});

	KeySetting.insert({ VK_LCONTROL,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_LSHIFT,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_LMENU,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_SPACE,
		[]()
		{

		}
		});

	KeySetting.insert({ VK_INSERT,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_DELETE,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_HOME,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_END,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_PRIOR,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NEXT,
		[]()
		{

		}
		});



	KeySetting.insert({ VK_LBUTTON,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_RBUTTON,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_LEFT,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_RIGHT,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_UP,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_DOWN,
		[]()
		{

		}
		});

	KeySetting.insert({ VK_NUMPAD0,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD1,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD2,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD3,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD4,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD5,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD6,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD7,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD8,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_NUMPAD9,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_MULTIPLY,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_ADD,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_SEPARATOR,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_SUBTRACT,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_DECIMAL,
		[]()
		{

		}
		});
	KeySetting.insert({ VK_DIVIDE,
		[]()
		{

		}
		});
}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::ComponentTick(float _DeltaTime)
{
	UActorComponent::ComponentTick(_DeltaTime);


}
