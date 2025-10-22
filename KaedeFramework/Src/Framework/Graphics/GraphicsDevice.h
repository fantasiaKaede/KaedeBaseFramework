#pragma once
class GraphicsDevice
{
public:
	//初期化
	//成功したらtrue
	bool Init();
private:
	GraphicsDevice() {}
	~GraphicsDevice() {}
private:
	//ファクトリーの作成
	//成功したらtrue
	bool CreateFactory();
	//デバイスの作成
	//成功したらtrue
	bool CreateDevice();
	enum class GPUTier
	{
		NVIDIA,
		Amd,
		Intel,
		Arm,
		Qualcomm,
		Kind,
	};
	ComPtr<ID3D12Device8>m_pDevice = nullptr;
	ComPtr<IDXGIFactory6>m_pDxgiFactory = nullptr;
	ComPtr<IDXGISwapChain4>m_pSwapChain = nullptr;
public:
	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};
