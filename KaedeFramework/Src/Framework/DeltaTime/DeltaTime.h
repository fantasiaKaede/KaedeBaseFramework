#pragma once

class DeltaTime {
public:
	
	

	void Update() 
	{
	
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<float> delta = now - m_prevTime;
		m_deltaTime = delta.count(); // 秒単位
		m_prevTime = now;
	}

	// 経過時間をゼロとして再初期化
	void Reset() 
	{
		m_prevTime = std::chrono::steady_clock::now();
		m_deltaTime = 0.0f;
	}

	// 秒単位のデルタタイムを返す
	float GetDeltaTime() const
	{
		return m_deltaTime;
	}
private:
	std::chrono::steady_clock::time_point m_prevTime;
	float m_deltaTime;
private:
	DeltaTime() : m_prevTime(std::chrono::steady_clock::now()),
		m_deltaTime(0.0f)
	{ }
	~DeltaTime() { ; }
public:
	static DeltaTime& Instance() 
	{
		static DeltaTime instance;
		return instance;
	}
};
