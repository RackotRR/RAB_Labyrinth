#include <assert.h>

#include "World.h"


std::optional<GameObject*> World::GetObjectAt(const Vector2& position) {
	// если есть объект на месте, то возвращаем указатель на него
	if (IsObjectAt(position)) {
		return gameObjects.at(position).get();
	}
	else {
		// если нет, то nullopt
		return std::nullopt;
	}
}

bool World::IsObjectAt(const Vector2& position) const {
	return gameObjects.contains(position);
}

void World::PlaceObject(GameObject&& object) {
	// на том месте не должно быть объекта
	assert(IsObjectAt(object.GetPosition()) == false);

	// добавляем новый объект на требуемое место
	gameObjects.emplace(object.GetPosition(), std::make_unique<GameObject>(std::move(object))); 
}

void World::DoForEachObject(std::function<void(GameObject*)> func) {
	std::for_each(gameObjects.begin(), gameObjects.end(), // проходим по всем элементам
		[&](TGameObjects::value_type& iter) { // лямбда, принимающая unique_ptr на GameObject - iterator
			auto* gameObject{ iter.second.get() };
			func(gameObject); 
		}); // выполняем требуемую функцию
}