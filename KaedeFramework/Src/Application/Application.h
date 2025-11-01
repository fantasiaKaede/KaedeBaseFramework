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

	
	void BeginUpdate();
	void PreUpdate();
	void Update();
	void PostUpdate();
	void EndUpdate();

	void BeginDraw(bool usePostProcess = true);
	void PreDraw();
	void Draw();
	void PostDraw();
	void DrawSprite();
	void EndDraw();
private:
	Window m_window;

public:
	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
};
