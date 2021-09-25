#pragma once

namespace LT {
	class Time
	{
	public:
		Time(float time = 0.f)
			: m_time(time)
		{}

		operator float() const { return m_time; }
		float GetSeconds() const { return m_time; }
		float GetMiliSeconds() const { return m_time * 1000.f; }
	private:
		float m_time;
	};
}