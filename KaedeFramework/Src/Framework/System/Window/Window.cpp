#include"Window.h"

LRESULT WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY://�E�B���h�E���j�����ꂽ�Ƃ�
		PostQuitMessage(0);//���b�Z�[�W���[�v�ɏI����`����
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);//������OS�ɔC����
		break;
	}
	return 0;
}

bool Window::Create(int clientWidth, int clientHeight, const std::wstring& titleName, const std::wstring& windowClassName)
{
	//�E�B���h�E�N���X�̓o�^
	HINSTANCE hInst = GetModuleHandle(0);
	
	//=======================================
	//�E�B���h�E�N���X�̐ݒ�
	//=======================================
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);				//�\���̂̃T�C�Y
	wc.lpfnWndProc = (WNDPROC)WindowProcedure;	//�E�B���h�E�v���V�[�W���̐ݒ�
	wc.lpszClassName = windowClassName.c_str();	//�N���X���̐ݒ�
	wc.hInstance = hInst;						//�C���X�^���X�n���h���̐ݒ�
	//Window�N���X�̓o�^
	if(!RegisterClassEx(&wc))
	{
		return false;
	}
	//�E�B���h�E�̍쐬
	m_hWnd = CreateWindow
	(
		windowClassName.c_str(),				//�N���X��
		titleName.c_str(),						//�^�C�g���o�[�̕�����
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,	//�E�B���h�E�X�^�C��
		0,										//����X���W
		0,										//����Y���W
		clientWidth,                            //�E�B���h�E��
		clientHeight,                           //�E�B���h�E��
		nullptr,								//�e�E�B���h�E�n���h��
		nullptr,								//���j���[�n���h��
		hInst,									//�C���X�^���X�n���h��
		this									//�ǉ��p�����[�^
	);
	if (m_hWnd==nullptr)return false;
	//�E�B���h�E�̕\��
	ShowWindow(m_hWnd, SW_SHOW);
	//�E�B���h�E�̍X�V
	UpdateWindow(m_hWnd);
	return true;
}

bool Window::ProcessMessage()
{
	//���b�Z�[�W�̎擾�Ə���
	MSG msg;
	while (PeekMessage(&msg,nullptr,0,0,PM_REMOVE))
	{
		if (msg.message == WM_QUIT)//�I�����b�Z�[�W��������false��Ԃ�
		{
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	
	}
	return true;
}
