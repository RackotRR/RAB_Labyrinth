#pragma once
#include "RRKeyboardState.h"

class RRController {
public:
	static RRController& Instance();

	const RRKeyboardState& GetKeyState() const {
		return keyState;
	}

	void Update();
private:
	RRKeyboardState keyState;

	RRController() = default;
	RRController(const RRController&) = delete;
	void operator=(const RRController&) = delete;
};