#pragma once
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <functional>

#include "Vector2.h"
#include "GameObject.h"

class World {
	// тип хранилища объектов
public:
	using TGameObjects = std::unordered_map<Vector2, std::unique_ptr<GameObject>, HashVector2>;

	std::optional<GameObject*> GetObjectAt(const Vector2& position);

	bool IsObjectAt(const Vector2& position) const;

	void PlaceObject(GameObject&& object);
	 
	void DoForEachObject(std::function<void(GameObject*)> func);
	 
private:
	TGameObjects gameObjects;
};