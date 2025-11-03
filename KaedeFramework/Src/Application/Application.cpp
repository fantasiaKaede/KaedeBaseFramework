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

	Mesh mesh;
	mesh.Create(&GraphicsDevice::Instance());

	RenderingSetting renderingSetting = {};
	renderingSetting.InputLayouts = { InputLayout::POSITION};
	renderingSetting.Formats = { DXGI_FORMAT_R8G8B8A8_UNORM };
	renderingSetting.IsDepth = false;
	renderingSetting.IsDepthMask = false;
	Shader shader;
	shader.Create(&GraphicsDevice::Instance(), L"SimpleShader", renderingSetting, {});
	
	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			GraphicsDevice::Instance().WaitForCommandQueue();//終了前にGPUの処理を待つ
			break;
		}
		//=========================================
		//
		// アプリケーション更新処理
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
		// アプリケーション描画処理
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
		GraphicsDevice::Instance().Prepare();
		shader.Begin(width, heigt);
		shader.DrawMesh(mesh);
		GraphicsDevice::Instance().ScreenFlip();
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
