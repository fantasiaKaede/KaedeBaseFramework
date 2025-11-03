#include "Shader.h"

void Shader::Create(GraphicsDevice* pGraphicsDevice, const std::wstring& filePath, const RenderingSetting& renderingSetting, const std::vector<RangeType>& rangeTypes)
{
	m_pDevice = pGraphicsDevice;
	LoadShaderFile(filePath);

	m_upRootSignature = std::make_unique<RootSignature>();
	m_upRootSignature->Create(m_pDevice, rangeTypes);

	m_upPipeline = std::make_unique<Pipeline>();
	m_upPipeline->SetRenderSettings(m_pDevice, m_upRootSignature.get(),
		renderingSetting.InputLayouts, renderingSetting.CullMode,
		renderingSetting.BlendMode, renderingSetting.PrimitiveTopologyType);
	m_upPipeline->Create({ m_pVSBlob,
		m_pHSBlob,
		m_pDSBlob,
		m_GSBlob,
		m_pPSBlobp },
		renderingSetting.Formats,
		renderingSetting.IsDepth,
		renderingSetting.IsDepthMask,
		renderingSetting.RTVCount,
		renderingSetting.IsWireFrame);

}

void Shader::Begin(int w, int h)
{
	m_pDevice->GetCommandList()->SetPipelineState(m_upPipeline->GetPipelineState());

	//ルートシグネチャのセット
	m_pDevice->GetCommandList()->SetGraphicsRootSignature(
		m_upRootSignature->GetRootSignature());
	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType =
		static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(m_upPipeline->GetTopologyType());
	switch (topologyType)
	{
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT:
		m_pDevice->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE:
		m_pDevice->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE:
		m_pDevice->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH:
		m_pDevice->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
		break;
	}
	D3D12_VIEWPORT viewport = {};
	D3D12_RECT rect = {};
	viewport.Width = static_cast<float>(w);
	viewport.Height = static_cast<float>(h);

	rect.right = w;
	rect.bottom = h;
	m_pDevice->GetCommandList()->RSSetViewports(1, &viewport);
	m_pDevice->GetCommandList()->RSSetScissorRects(1, &rect);

}

void Shader::DrawMesh(const Mesh& mesh)
{
	mesh.DrawInstanced();
}

void Shader::LoadShaderFile(const std::wstring& filePath)
{
	ID3DInclude* include =D3D_COMPILE_STANDARD_FILE_INCLUDE;
	UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	ID3DBlob* pErrorBlob = nullptr;
	std::wstring format = L".hlsl";
	std::wstring currentFilePath = L"Src/Framework/Graphics/Shader/";
	//頂点シェーダーのコンパイル
	{
		std::wstring fullPath = currentFilePath + filePath + L"_VS" + format;
		auto hr= D3DCompileFromFile(fullPath.c_str(),
			nullptr,
			include,
			"main",
			"vs_5_0",
			flag,
			0,
			&m_pVSBlob,
			&pErrorBlob);
		if (FAILED(hr))
		{
			assert(0 && "頂点シェーダーのコンパイルに失敗");
		}
	}
	//ハルシェーダーのコンパイル
	{
		std::wstring fullPath = currentFilePath + filePath + L"_HS" + format;
		auto hr = D3DCompileFromFile(fullPath.c_str(),
			nullptr,
			include,
			"main",
			"hs_5_0",
			flag,
			0,
			&m_pHSBlob,
			&pErrorBlob);
	}
	//ドメインシェーダーのコンパイル
	{
		std::wstring fullPath = currentFilePath + filePath + L"_DS" + format;
		auto hr = D3DCompileFromFile(fullPath.c_str(),
			nullptr,
			include,
			"main",
			"ds_5_0",
			flag,
			0,
			&m_pDSBlob,
			&pErrorBlob);
	}
	//ジオメトリシェーダーのコンパイル
	{
		std::wstring fullPath = currentFilePath + filePath + L"_GS" + format;
		auto hr = D3DCompileFromFile(fullPath.c_str(),
			nullptr,
			include,
			"main",
			"gs_5_0",
			flag,
			0,
			&m_GSBlob,
			&pErrorBlob);
	}
	//ピクセルシェーダーのコンパイル
	{
		std::wstring fullPath = currentFilePath + filePath + L"_PS" + format;
		auto hr = D3DCompileFromFile(fullPath.c_str(),
			nullptr,
			include,
			"main",
			"ps_5_0",
			flag,
			0,
			&m_pPSBlobp,
			&pErrorBlob);
		if (FAILED(hr))
		{
			assert(0 && "ピクセルシェーダーのコンパイルに失敗");
		}
	}
}
