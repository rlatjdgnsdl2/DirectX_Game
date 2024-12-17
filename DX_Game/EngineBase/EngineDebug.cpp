#include "PreCompile.h"
#include "EngineDebug.h"


namespace UEngineDebug
{
	void LeakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	// 분리해야 하겠네요
	void OutPutString(const std::string& Text)
	{
		std::string ResultText = Text + "\n";
		OutputDebugStringA(ResultText.c_str());
	}
    void StartConsole() {
        AllocConsole();
        FILE* Console;
        if (freopen_s(&Console, "CONOUT$", "w", stdout) != 0) {
            return;
        }
        if (freopen_s(&Console, "CONOUT$", "w", stderr) != 0) {
            return;
        }
        if (freopen_s(&Console, "CONIN$", "r", stdin) != 0) {
            return;
        }
        // C++ 스트림과 C 스트림의 동기화 활성화
        std::ios::sync_with_stdio(true); 
    }
    void EndConsole() {
		fclose(stdout);
		fclose(stderr);
		fclose(stdin);
        FreeConsole();
    }
}