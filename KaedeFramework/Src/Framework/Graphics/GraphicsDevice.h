#pragma once
class RTVHeap;
class GraphicsDevice
{
public:
	//初期化
	//成功したらtrue
	bool Init(HWND hwnd, int w, int h);

	//画面（スワップチェイン）の切り替え
	void ScreenFlip();

	//コマンドキューの同期待ち
	void WaitForCommandQueue();
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

	//コマンドリストの作成
	//成功したらtrue
	bool CreateCommandList();

	//スワップチェインの作成
	//成功したらtrue
	bool CreateSwapchain(HWND hwnd, int width, int height);

	//スワップチェインRTVの作成
	//成功したらtrue
	bool CreateSwapchainRTV();


	//Fenceの作成
	//成功したらtrue
	bool CreateFence();

	//リソースとして引数に渡したバッファの扱いを変更する関数
	void SetResourceBarrier
	(
		ID3D12Resource*pResource,
		D3D12_RESOURCE_STATES before,
		D3D12_RESOURCE_STATES after
		);
	//デバッグレイヤー
	void EnableDebugLayer();
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
	

	ComPtr<ID3D12CommandAllocator> m_pCmdAllocator = nullptr;
	ComPtr<ID3D12GraphicsCommandList6>m_pCmdList = nullptr;
	ComPtr<ID3D12CommandQueue>m_pCmdQueue = nullptr;

	ComPtr<IDXGISwapChain4>m_pSwapChain = nullptr;

	std::array<ComPtr<ID3D12Resource>, 2>m_pSwapchainBuffers;
	std::unique_ptr<RTVHeap>m_pRTVHeap = nullptr;

	ComPtr<ID3D12Fence>m_pFence = nullptr;
	UINT64 m_fenceVal = 0;
public:
	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};
