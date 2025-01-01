#pragma once

namespace Light {
	class DeltaTime
	{
	public:
		//change of Time in seconds.
		static DeltaTime zeroDeltaTime;

		DeltaTime(double seconds)
			: m_seconds(seconds) { }

		int getSeconds() const { return (int)m_seconds; }
		float getMiliseconds() const{ return m_seconds * 1000; }
		float getTime() const { return m_seconds; }

		void operator-(DeltaTime time) {
			m_seconds -= time.m_seconds;
		}

		void operator+(DeltaTime time) {
			m_seconds += time.m_seconds;
		}

	private:
		float m_seconds;
	};

	DeltaTime DeltaTime::zeroDeltaTime = DeltaTime(0);
}