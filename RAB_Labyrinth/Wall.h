#pragma once
#include "GameObject.h"

class Wall : public GameObject  {
public:
	Wall() = default;
	explicit Wall(Vector2 position) : GameObject{ position } {}
	virtual ~Wall() {}
private:

};
