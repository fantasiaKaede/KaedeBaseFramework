#pragma once
#include<Windows.h>
#include<string>
class Window
{
public:
	//ウィンドウの生成
	//　　　　　　　　横幅　　　　　　縦幅　　　　　　　　　タイトル名　　　　　　　　　クラス名　　　　　　　　　　　　　　
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);
	bool ProcessMessage();
private:
	HWND m_hWnd;
};

