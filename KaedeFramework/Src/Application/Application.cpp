#include "Application.h"

//エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//メモリーリークを知らせる

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);//COM初期化

	//アプリケーションの実行
	Application::Instance().Excute();

	CoUninitialize();//COM解放
	return 0;
}



void Application::Excute()
{
	static const int width = 1280;
	static const int heigt = 720;
	if (!m_window.Create(1280, 720, L"KaedeFramework", L"Window"))
	{
		assert(0 && "ウィンドウの生成に失敗");
		return;
	}


	if (!GraphicsDevice::Instance().Init(m_window.GetWndHandle(),width,heigt))
	{
		assert(0, && "グラフィックスデバイス初期化失敗");
		return;
	}


	while (true)
	{
		if (!m_window.ProcessMessage())break;
	}
}
