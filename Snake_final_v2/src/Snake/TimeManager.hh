
#pragma once
#include <SDL/SDL.h>
#include <functional>
#include "IOManager.hh"

#define TM TimeManager::Instance()
class TimeManager {
public:
	float FPS=10.0f;
	float TICKS_PER_FRAME{ 1.f / FPS };
	inline static TimeManager &Instance(void) {
		static TimeManager timeManager;
		return timeManager;
	}
	void Update(std::function<void()> gameUpdate) {
		m_deltatime = float(GetCurTime() - m_lastTime) / SDL_GetPerformanceFrequency();
		m_lastTime = GetCurTime();
		m_renderTime += m_deltatime;
		while (m_renderTime >= TICKS_PER_FRAME) {
			gameUpdate();
			m_renderTime -= TICKS_PER_FRAME;
		}
	}
	inline Uint64 GetCurTime() { return SDL_GetPerformanceCounter(); };
	inline float GetDeltaTime() { return m_deltatime; };
	void setVel(float fps) {
		FPS = fps;
		TICKS_PER_FRAME = 1.F / FPS;
	}
	float getVel() {
		return FPS;
	}
private:
	TimeManager() = default;
	TimeManager(const TimeManager &rhs) = delete;
	TimeManager &operator=(const TimeManager &rhs) = delete;
private:
	float m_deltatime{ 0.f }; // Delta time in seconds
	Uint64 m_lastTime{ GetCurTime() }; // Last time sample in seconds
	float m_renderTime{ 0 }; // Time control for rendering
};