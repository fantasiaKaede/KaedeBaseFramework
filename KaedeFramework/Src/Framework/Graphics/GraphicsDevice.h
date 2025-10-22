#pragma once
class GraphicsDevice
{
public:
	//������
	//����������true
	bool Init();
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
