#include "Application.h"

//�G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//�������[���[�N��m�点��

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);//COM������

	//�A�v���P�[�V�����̎��s
	Application::Instance().Excute();

	CoUninitialize();//COM���
	return 0;
}



void Application::Excute()
{
	static const int width = 1280;
	static const int heigt = 720;
	if (!m_window.Create(1280, 720, L"KaedeFramework", L"Window"))
	{
		assert(0 && "�E�B���h�E�̐����Ɏ��s");
		return;
	}


	if (!GraphicsDevice::Instance().Init(m_window.GetWndHandle(),width,heigt))
	{
		assert(0, && "�O���t�B�b�N�X�f�o�C�X���������s");
		return;
	}


	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			GraphicsDevice::Instance().WaitForCommandQueue();//�I���O��GPU�̏�����҂�
			break;
		}
		GraphicsDevice::Instance().ScreenFlip();
		//=========================================
		//
		// �A�v���P�[�V�����X�V����
		//
		//=========================================
		DeltaTime::Instance().Update();
		BeginUpdate();
		{
			PreUpdate();

			Update();

			PostUpdate();
		}
		EndUpdate();

		//=========================================
		//
		// �A�v���P�[�V�����`�揈��
		//
		//=========================================

		BeginDraw();
		{
			PreDraw();

			Draw();

			PostDraw();

			DrawSprite();
		}
		EndDraw();
	}
}

void Application::BeginUpdate()
{
}

void Application::PreUpdate()
{
}

void Application::Update()
{
}

void Application::PostUpdate()
{
}

void Application::EndUpdate()
{
}

void Application::BeginDraw(bool usePostProcess)
{
}

void Application::PreDraw()
{
}

void Application::Draw()
{
}

void Application::PostDraw()
{
}

void Application::DrawSprite()
{
}

void Application::EndDraw()
{
}
