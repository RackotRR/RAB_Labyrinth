#pragma once
#include <SDL.h>
#include "RRGameIO.h"

class RRGameIO_SDL : public RRGameIO
{
public: 
	void Initialize() override;
	void Shutdown() override;

	void Begin() override;
	void End() override;


	int GetWinWidth() const override;
	int GetWinHeight() const override; 

	// нарисовать текстуру
	void DrawTexture(const Rectangle& rect, const RRTexture& texture) override;
	// нарисовать текстуру с поворотом
	void DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle) override;
	// нарисовать текстуру с поворотом и отражением
	void DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle, DrawFlip dflip) override;

	// вывести строку на экран
	void DrawLine(const Vector2& topLeft, Font font, const std::string& str) override;

	// нарисовать прямоугольник
	void DrawRectangle(const Rectangle& rect, const RRColor& color) override;

	RRTexture LoadTextureFromFile(std::string_view path) override;
private:   
	bool Initialized{ false };

	SDL_Window* window{};
	SDL_Renderer* renderer{};

	int windowWidth{}, windowHeight{}; 
};

