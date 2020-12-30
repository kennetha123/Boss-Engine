#pragma once

namespace BossEngine
{
	class DeltaTime
	{
	public:
		DeltaTime(float time = 0.0f)
			: m_Time(time)
		{

		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; }
	
	private:
		float m_Time;
	};
}