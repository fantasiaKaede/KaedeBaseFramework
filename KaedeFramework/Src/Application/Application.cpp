#include "Application.h"

//�G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�A�v���P�[�V�����̎��s
	Application::Instance().Excute();
	return 0;
}



void Application::Excute()
{
	if (!m_window.Create(1280, 720, L"KaedeFramework", L"Window"))
	{
		assert(0 && "�E�B���h�E�̐����Ɏ��s");
		return;
	}
	while (true)
	{
		if (!m_window.ProcessMessage())break;
	}
}
