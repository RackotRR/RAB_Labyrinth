#include "RRController.h"
#include <SDL.h>

void RRController::Update() { 
	SDL_Event event;
	while (SDL_PollEvent(&event));
	// получаем данные ввода с клавиатуры
	keyState.Update((unsigned char*)SDL_GetKeyboardState(NULL));
}

RRController& RRController::Instance() {
	static RRController instance;
	return instance;
}

