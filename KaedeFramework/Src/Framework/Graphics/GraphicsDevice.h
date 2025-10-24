#pragma once
class RTVHeap;
class GraphicsDevice
{
public:
	//������
	//����������true
	bool Init(HWND hwnd, int w, int h);
private:
	GraphicsDevice() {}
	~GraphicsDevice() {}
private:
	//�t�@�N�g���[�̍쐬
	//����������true
	bool CreateFactory();
	//�f�o�C�X�̍쐬
	//����������true
	bool CreateDevice();

	//�R�}���h���X�g�̍쐬
	//����������true
	bool CreateCommandList();

	//�X���b�v�`�F�C���̍쐬
	//����������true
	bool CreateSwapchain(HWND hwnd, int width, int height);

	//�X���b�v�`�F�C��RTV�̍쐬
	//����������true
	bool CreateSwapchainRTV();
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

public:
	static GraphicsDevice& Instance()
	{
		static GraphicsDevice instance;
		return instance;
	}
};
