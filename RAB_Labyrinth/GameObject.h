#pragma once
#include "Vector2.h"
#include <unordered_map>
#include <optional>
#include <assert.h>
#include <memory>

#include "Component.h"
#include "DrawingComponent.h"

class GameObject { 
public:
	GameObject() = default;
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) noexcept = default; 
	
	explicit GameObject(Vector2 position) : position{ position } {} 
	virtual ~GameObject() = default;

	/* EXAMPLE
	GameObject object;
	MoveComponent mc;
	object.AddComponent(std::move(mc));
	object.AddComponent(HPComponent{});

	auto moveComponentOpt{ object.GetComponent<MoveComponent>() };
	if (moveComponentOpt.has_value()) {
		auto moveComponent{ moveComponentOpt.value() };
		// usage of moveComponent
		std::cout << "found move component: " << typeid(*moveComponent).name()  << std::endl;
	}
	*/
	template<typename TComponent>
	std::optional<TComponent*> GetComponent() {
		// ���� ��� ��� ��������� ����������
		size_t componentHash{ typeid(TComponent).hash_code() };

		// ���� ����� ���������� ����
		if (components.contains(componentHash)) {
			// �������� � ���������� ���� (down cast) 
			return static_cast<TComponent*>(components[componentHash].get());
		}
		else {
			// ���� ���, �� nullopt
			return std::nullopt;
		}
	}
	  
	// �������� ������������ ����������
	template<typename TComponent>
	void AddComponent(TComponent componentR = TComponent{}) {
		auto component{ std::make_unique<TComponent>(std::move(componentR)) };
		this->AddComponent(std::move(component));
	}  
	 
	void SetPosition(Vector2 position) {
		this->position = position;
	}

	Vector2 GetPosition() const {
		return position;
	}

protected:

	Vector2 position{ Vector2::WrongVector };
	std::unordered_map<size_t, std::unique_ptr<Component>> components;

private:
	// �������� ���������� � �������
	template<typename TComponent>
	void AddComponent(std::unique_ptr<TComponent> component) {
		// �������� �� ����������� up cast, ���� ����� ����������, �� �������� � �����
		assert(dynamic_cast<Component*>(component.get()) != nullptr);

		// ��� ����� ����������
		size_t componentHash{ typeid(TComponent).hash_code() };

		// ���� ����� ���������� ��� ����, �� ��� �������� � �����
		assert(!components.contains(componentHash));

		// ��������� ����� ���������� 
		components.emplace(componentHash, std::move(component));
	}
};