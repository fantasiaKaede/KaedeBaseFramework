#include "Mesh.h"

void Mesh::Create(GraphicsDevice* pGraphicsDevice)
{
	m_pDevice = pGraphicsDevice;
	
	
	//���_�̍��W
	m_vertices[0] = {-1.0f,-1.0f};
	m_vertices[1] = { 1.0f,1.0f };
	m_vertices[2] = { 0.0f,1.0f };

	D3D12_HEAP_PROPERTIES heapProps = {};
	heapProps.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProps.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProps.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeof(Math::Vector3) * m_vertices.size();
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	auto hr= m_pDevice->GetDevice()->CreateCommittedResource(
		&heapProps,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&m_pVBuffer)
	);
	if (FAILED(hr))
	{
		assert(0 && "���_�o�b�t�@�̐����Ɏ��s");
		return;
	}
	//���_�o�b�t�@�Ƀf�[�^�]��
	Math::Vector3* vbMap = nullptr;
	{
		m_pVBuffer->Map(0, nullptr, (void**)&vbMap);
		std::copy(std::begin(m_vertices),std::end(m_vertices), vbMap);
		m_pVBuffer->Unmap(0, nullptr);
	}
}

void Mesh::DrawInstanced()const
{
	m_pDevice->GetCommandList()->IASetVertexBuffers(0,1,&m_vbView);
	m_pDevice->GetCommandList()->DrawInstanced(3,1,0,0);
}
