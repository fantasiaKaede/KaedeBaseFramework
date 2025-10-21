#pragma once
#include<Windows.h>
#include<string>
class Window
{
public:
	//�E�B���h�E�̐���
	//�@�@�@�@�@�@�@�@�����@�@�@�@�@�@�c���@�@�@�@�@�@�@�@�@�^�C�g�����@�@�@�@�@�@�@�@�@�N���X���@�@�@�@�@�@�@�@�@�@�@�@�@�@
	bool Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName);
	bool ProcessMessage();
private:
	HWND m_hWnd;
};

