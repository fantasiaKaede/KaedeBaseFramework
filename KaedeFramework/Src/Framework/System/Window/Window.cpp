#include"Window.h"

LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY://ウィンドウが破棄されたとき
		PostQuitMessage(0);//メッセージループに終了を伝える
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);//処理をOSに任せる
		break;
	}
	return 0;
}

bool Window::Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName)
{
	//ウィンドウクラスの登録
	HINSTANCE hInst = GetModuleHandle(0);
	
	//=======================================
	//ウィンドウクラスの設定
	//=======================================
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);				//構造体のサイズ
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;	//ウィンドウプロシージャの設定
	wc.lpszClassName = windowClassName.c_str();	//クラス名の設定
	wc.hInstance = hInst;						//インスタンスハンドルの設定
	//Windowクラスの登録
	if(!RegisterClassEx(&wc))
	{
		return false;
	}
	//ウィンドウの作成
	m_hWnd = CreateWindow
	(
		windowClassName.c_str(),				//クラス名
		titleName.c_str(),						//タイトルバーの文字列
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,	//ウィンドウスタイル
		0,										//初期X座標
		0,										//初期Y座標
		clientWidth,                            //ウィンドウ幅
		clientHeight,                           //ウィンドウ高
		nullptr,								//親ウィンドウハンドル
		nullptr,								//メニューハンドル
		hInst,									//インスタンスハンドル
		this									//追加パラメータ
	);
	if (m_hWnd==nullptr)return false;
	//ウィンドウの表示
	ShowWindow(m_hWnd, SW_SHOW);
	//ウィンドウの更新
	UpdateWindow(m_hWnd);
	return true;
}

bool Window::ProcessMessage()
{
	//メッセージの取得と処理
	MSG msg;
	while (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
	{
		if (msg.message == WM_QUIT)//終了メッセージが来たらfalseを返す
		{
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	
	}
	return true;
}
