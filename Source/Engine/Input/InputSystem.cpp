#include "InputSystem.h"

namespace kiko
{
	bool InputSystem::Initialize()
	{
		int numKeys;
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		m_keyboardState.resize(numKeys);
		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;

		return true;
	}
	void InputSystem::Shutdown()
	{
		//
	}
	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		m_prevKeyboardState = m_keyboardState;

		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = vec2{ x , y };
		
		m_prevMouseButtonState = m_mouseButtonState;
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
	}
}
