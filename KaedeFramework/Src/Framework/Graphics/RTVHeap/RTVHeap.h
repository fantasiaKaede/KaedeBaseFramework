#pragma once
class RTVHeap
{
public:
	RTVHeap(){}
	~RTVHeap(){}
	//ヒープ作成
	//成功したらtrue
	bool Create(ID3D12Device* pDevice, int useCount);
	//RTV作成
	//バッファーのポインタ
	//ヒープの紐付けられた登録番号
	int CreateRTV(ID3D12Resource* pBuffer);
	//RTVのCPU側アドレスを返す関数
	D3D12_CPU_DESCRIPTOR_HANDLE GetRTVCPUHandle(int number);
private:
	ID3D12Device* m_pDevice = nullptr;
	ComPtr<ID3D12DescriptorHeap>m_pHeap = nullptr;
	int m_useCount = 0;
	int m_incrementSize = 0;
	int m_nextRegistNumber = 0;
};

