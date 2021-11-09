#pragma once
#include <string>
#include "Vector2.h"
#include "Rectangle.h"  
#include "RRColor.h"

//#include "RRTexture.h" 
class RRTexture;

enum class DrawFlip {
	none = 0,
	horizontal,
	vertical,
};

enum class Font {
	Menu,
	Treasures
};

class RRGameIO {
public:
	static RRGameIO& Instance();
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Begin() = 0;
	virtual void End() = 0;
	 
	virtual int GetWinWidth() const = 0;
	virtual int GetWinHeight() const = 0; 

	  
	// нарисовать текстуру
	virtual void DrawTexture(const Rectangle& rect, const RRTexture& texture) = 0;
	// нарисовать текстуру с поворотом
	virtual void DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle) = 0;
	// нарисовать текстуру с поворотом и отражением
	virtual void DrawTexture(const Rectangle& rect, const RRTexture& texture, double angle, DrawFlip dflip) = 0;

	// вывести строку на экран
	virtual void DrawLine(const Vector2& topLeft, Font font, const std::string& str) = 0;

	// нарисовать прямоугольник
	virtual void DrawRectangle(const Rectangle& rect, const RRColor& color) = 0;

	virtual RRTexture LoadTextureFromFile(std::string_view path) = 0;
protected:
	RRGameIO() {}
	RRGameIO(const RRGameIO&) = delete;
	RRGameIO& operator= (const RRGameIO&) = delete;
	virtual ~RRGameIO() {}
};

