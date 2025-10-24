#pragma once
class RTVHeap
{
public:
	RTVHeap(){}
	~RTVHeap(){}
	//�q�[�v�쐬
	//����������true
	bool Create(ID3D12Device* pDevice, int useCount);
	//RTV�쐬
	//�o�b�t�@�[�̃|�C���^
	//�q�[�v�̕R�t����ꂽ�o�^�ԍ�
	int CreateRTV(ID3D12Resource* pBuffer);
	//RTV��CPU���A�h���X��Ԃ��֐�
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUHandle(int number);
private:
	ID3D12Device* m_pDevice = nullptr;
	ComPtr<ID3D12DescriptorHeap>m_pHeap = nullptr;
	int m_useCount = 0;
	int m_incrementSize = 0;
	int m_nextRegistNumber = 0;
};

