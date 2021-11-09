#pragma once
/*
Абстракция цвета
*/
struct RRColor {
	RRColor() : RRColor{ 0, 0, 0, 255 } {}
	RRColor(int r, int g, int b) : RRColor{ r, g, b, 255} {}
	RRColor(int r, int g, int b, int a) : r{ r }, g{ g }, b{ b }, a{ a } {}
	int r, g, b, a;
};