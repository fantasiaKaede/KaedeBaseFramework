#pragma once
#include"../Framework/System/Window/Window.h"
class Application
{
public:
	//�A�v���P�[�V�����̎��s
	void Excute();
private:
	Application(){}
	~Application(){}
	
private:
	Window m_window;

public:
	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
};
