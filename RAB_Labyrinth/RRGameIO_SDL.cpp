#include "RRGameIO_SDL.h"
#include "RRTexture.h"
#include "RRTextOutput.h"
#include "RRTextureManager.h"
#include "RRGameTime.h"

#include <SDL_image.h>
#include <stdexcept>
 
RRGameIO& RRGameIO::Instance() {
	static RRGameIO_SDL instance;
	return instance;
} 

void RRGameIO_SDL::Initialize() {  
	// ���� �������� �������� ���������������� SDL, �� ���-�� ��� �� ���
	assert(SDL_WasInit(SDL_INIT_EVERYTHING) == false);

	// �������� ���������������� ��� ������� SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
		throw std::runtime_error{ "Unable to initialize SDL: " + std::string{ SDL_GetError() } };
	}

	// �������� ������� ������
	SDL_Rect displayBounds;
	if (SDL_GetDisplayBounds(0, &displayBounds) != 0) { 
		throw std::runtime_error{ "SDL_GetDisplayBounds failed: " + std::string{ SDL_GetError() } };
	}
	else {
		// �� �� ���� ����� ��������� ����
		windowHeight = static_cast<int>( displayBounds.h * 0.8 );
		windowWidth = static_cast<int>( displayBounds.w * 0.8 );
	}

	// ������ ����
	window = SDL_CreateWindow("Red&Blue: Labyrinth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, SDL_WINDOW_VULKAN | SDL_WINDOW_BORDERLESS);
	if (!window) { 
		throw std::runtime_error{ "Failed to create window: " + std::string{ SDL_GetError() } };
	}

	// ������ ������
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		throw std::runtime_error{ "Failed to create renderer: " + std::string{ SDL_GetError() } };
	}

	// ����� ������������
	if (SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD) != 0) { 
		throw std::runtime_error{ "Failed to set render draw blend mode: " + std::string{ SDL_GetError() } };
	}

	// ������ ��� �������� ������� � PNG
	if (IMG_Init(IMG_INIT_PNG) == 0) { 
		throw std::runtime_error{ "Unable to initialize SDL_image: " + std::string{ SDL_GetError() } };
	}

	// �������� ��������� �������
	RRTextureManager::Instance().Initialize();
	 
	// ������ ��� ������ ��������� ������� �� ������
	RRTextOutput::Instance().Initialize(renderer);

	Initialized = true;
}

void RRGameIO_SDL::Shutdown() {
	RRTextOutput::Instance().Shutdown();
	RRTextureManager::Instance().Shutdown();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void RRGameIO_SDL::Begin() { 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}
void RRGameIO_SDL::End() { 
	auto passedTime{ RRGameTime::Instance().GetPassedTime() };
	if (passedTime == 0) {
		passedTime = 1;
	}
	int FPS = 1000 / passedTime;
	DrawLine(Vector2(windowWidth - 50, 0), Font::Treasures, std::to_string(FPS));
	SDL_RenderPresent(renderer);
}
  
int RRGameIO_SDL::GetWinWidth() const { 
	return windowWidth;
}
int RRGameIO_SDL::GetWinHeight() const { 
	return windowHeight;
}
  

// ���������� ��������
void RRGameIO_SDL::DrawTexture(const Rectangle& rect, const RRTexture& texture) { 
	assert(Initialized == true);

	DrawTexture(rect, texture, 0, DrawFlip::none);
}
// ���������� �������� � ���������
void RRGameIO_SDL::DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle) {
	assert(Initialized == true);

	DrawTexture(rect, texture, angle, DrawFlip::none);
}
// ���������� �������� � ��������� � ����������
void RRGameIO_SDL::DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle, DrawFlip dflip) {
	assert(Initialized == true);

	SDL_Rect r{ rect.x, rect.y, rect.width, rect.height }; // ��� �� ����� ��������

	SDL_RendererFlip flip{ SDL_FLIP_NONE }; // ���������
	switch (dflip)
	{
	case DrawFlip::horizontal:
		flip = SDL_FLIP_HORIZONTAL;
		break;
	case DrawFlip::vertical:
		flip = SDL_FLIP_VERTICAL;
		break; 
	}

	// ������
	SDL_RenderCopyEx(renderer,
		texture.Get(), // ���������
		nullptr, // ��� ��������
		&r, // ���
		angle, // ���� ��������
		nullptr, // ������������ ������
		flip); // ���������
}

// ������� ������ �� �����
void RRGameIO_SDL::DrawLine(const Vector2& topLeft, Font font, const std::string& str) {
	assert(Initialized == true);

	RRTextOutput::Instance().DrawLine(topLeft, font, str);
}

// ���������� �������������
void RRGameIO_SDL::DrawRectangle(const Rectangle& rect, const RRColor& color) {
	assert(Initialized == true);

	SDL_Rect r{ rect.x, rect.y, rect.width, rect.height };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &r);
}

RRTexture RRGameIO_SDL::LoadTextureFromFile(std::string_view path) { 
	SDL_Surface* surface{ IMG_Load(path.data()) };
	if (!surface) { 
		throw std::runtime_error{ "Failed to load texture file: " + std::string{ path } };
	}

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer, surface) };
	SDL_FreeSurface(surface);
	if (!texture) { 
		throw std::runtime_error{ "Failed to convert surface to texture for " + std::string{ path } };
	}

	return RRTexture{ texture };
}
