#include "RootSignature.h"

void RootSignature::Create(GraphicsDevice* pGraphicsDevice, const std::vector<RangeType>& rangeTypes)
{
	m_pDevice = pGraphicsDevice;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	int rangeCount = (int)rangeTypes.size();

	//レンジ数分のルートパラメータを作成
	std::vector<D3D12_ROOT_PARAMETER> rootParams(rangeCount);
	std::vector<D3D12_DESCRIPTOR_RANGE> ranges(rangeCount);
	//SRVの数だけSamplerを作成
	int samplerCount = 0;
	for (int i = 0; i < (int)rangeTypes.size(); ++i)
	{
		if(rangeTypes[i]==RangeType::SRV)
		{
			++samplerCount;
		}
	}
	//指定された順に設定
	samplerCount = 0;
	bool bSampler = false;
	int cbvCount = 0;
	int uavCount = 0;
	for (int i = 0; i < rangeCount; ++i)
	{
		switch (rangeTypes[i])
		{
		case RangeType::CBV:
			CreateRanges(ranges[i], RangeType::CBV, cbvCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++cbvCount;
			break;
		case RangeType::SRV:
			CreateRanges(ranges[i], RangeType::SRV, samplerCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++samplerCount;
			bSampler = true;
			break;
		case RangeType::UAV:
			CreateRanges(ranges[i], RangeType::UAV, uavCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++uavCount;
			break;
		default:
			break;
		}
	}
	std::array<D3D12_STATIC_SAMPLER_DESC, 4>pStaticSamplerDescs = {};
	if (bSampler)
	{
		//サンプラーの作成
		CreateSampler(pStaticSamplerDescs[0], TextureAddressMode::Wrap, D3D12Filter::Point, 0);
		CreateSampler(pStaticSamplerDescs[1], TextureAddressMode::Clamp, D3D12Filter::Point, 1);
		CreateSampler(pStaticSamplerDescs[2], TextureAddressMode::Wrap, D3D12Filter::Linear, 2);
		CreateSampler(pStaticSamplerDescs[3], TextureAddressMode::Clamp, D3D12Filter::Linear, 3);
	}
	rootSignatureDesc.pParameters = bSampler ? rootParams.data() : nullptr;
	rootSignatureDesc.NumParameters = bSampler ? 4 : 0;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams.data();
	rootSignatureDesc.NumStaticSamplers = (int)rangeTypes.size();
	ID3DBlob* pErrorBlob = nullptr;
	auto hr = D3D12SerializeRootSignature(&rootSignatureDesc,
		D3D_ROOT_SIGNATURE_VERSION_1_0,
		&m_pRootBlob,
		&pErrorBlob);
	if (FAILED(hr))
	{
		assert(0 && "ルートシグネチャの初期化に失敗");
	}
	hr = m_pDevice->GetDevice()->CreateRootSignature(
		0,
		m_pRootBlob->GetBufferPointer(),
		m_pRootBlob->GetBufferSize(),
		IID_PPV_ARGS(&m_pRootSignature));
	if (FAILED(hr))
		{
		assert(0 && "ルートシグネチャの作成に失敗");
	}
}

void RootSignature::CreateRanges(D3D12_DESCRIPTOR_RANGE& pRange, RangeType type, int count)
{
}

void RootSignature::CreateSampler(D3D12_STATIC_SAMPLER_DESC& pSamplerDesc, TextureAddressMode mode, D3D12Filter filter, int count)
{
}
