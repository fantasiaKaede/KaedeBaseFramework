#pragma once
enum class RangeType
{
	CBV,
	SRV,
	UAV,
};

enum class TextureAddressMode
{
	Wrap,
	Clamp,
};

enum class D3D12Filter
{
	Point,
	Linear,
};

class RootSignature
{
public:
	RootSignature(){}
	~RootSignature(){}

	//作成
	void Create(GraphicsDevice* pGraphicsDevice,const std::vector<RangeType>&rangeTypes);
	//ルートシグネチャの取得
	ID3D12RootSignature* GetRootSignature()const { return m_pRootSignature.Get(); }
private:
	//レンジの作成
	void CreateRanges(D3D12_DESCRIPTOR_RANGE& pRange, RangeType type, int count);
	//サンプラーの作成
	void CreateSampler(D3D12_STATIC_SAMPLER_DESC& pSamplerDesc, TextureAddressMode mode,
		D3D12Filter filter, int count);
	GraphicsDevice* m_pGraphicsDevice = nullptr;
	ComPtr<ID3DBlob>m_pRootBlob = nullptr;
	ComPtr<ID3D12RootSignature>m_pRootSignature = nullptr;
};

