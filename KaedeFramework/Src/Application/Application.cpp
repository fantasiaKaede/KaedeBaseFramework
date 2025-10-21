#include "Application.h"

//エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//アプリケーションの実行
	Application::Instance().Excute();
	return 0;
}



void Application::Excute()
{
	if (!m_window.Create(1280, 720, L"KaedeFramework", L"Window"))
	{
		assert(0 && "ウィンドウの生成に失敗");
		return;
	}
	while (true)
	{
		if (!m_window.ProcessMessage())break;
	}
}
