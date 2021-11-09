#include <assert.h>

#include "World.h"


std::optional<GameObject*> World::GetObjectAt(const Vector2& position) {
	// ���� ���� ������ �� �����, �� ���������� ��������� �� ����
	if (IsObjectAt(position)) {
		return gameObjects.at(position).get();
	}
	else {
		// ���� ���, �� nullopt
		return std::nullopt;
	}
}

bool World::IsObjectAt(const Vector2& position) const {
	return gameObjects.contains(position);
}

void World::PlaceObject(GameObject&& object) {
	// �� ��� ����� �� ������ ���� �������
	assert(IsObjectAt(object.GetPosition()) == false);

	// ��������� ����� ������ �� ��������� �����
	gameObjects.emplace(object.GetPosition(), std::make_unique<GameObject>(std::move(object))); 
}

void World::DoForEachObject(std::function<void(GameObject*)> func) {
	std::for_each(gameObjects.begin(), gameObjects.end(), // �������� �� ���� ���������
		[&](TGameObjects::value_type& iter) { // ������, ����������� unique_ptr �� GameObject - iterator
			auto* gameObject{ iter.second.get() };
			func(gameObject); 
		}); // ��������� ��������� �������
}