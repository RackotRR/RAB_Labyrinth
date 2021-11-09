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
	GameObject(GameObject&&) = default; 
	
	explicit GameObject(Vector2 position) : position{ position } {} 
	virtual ~GameObject() {}


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
		// берём хэш код требуемой компоненты
		size_t hashCode{ typeid(TComponent).hash_code() };

		// если такая компонента есть
		if (components.contains(hashCode)) {
			// приводим к требуемому типу (down cast) 
			return static_cast<TComponent*>(components[hashCode].get());
		}
		else {
			// если нет, то nullopt
			return std::nullopt;
		}
	}
	  
	// добавить существующую компоненту
	template<typename TComponent>
	void AddComponent(TComponent&& componentR) {
		auto component{ std::make_unique<TComponent>(std::move(componentR)) }; 
		this->AddComponent(std::move(component));
	} 
	// добавить новую компоненту по умолчанию
	template<typename TComponent>
	void AddComponent() {
		auto component{ std::make_unique<TComponent>() };
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
	// добавить компоненту в таблицу
	template<typename TComponent>
	void AddComponent(std::unique_ptr<TComponent> component) {
		// проверка на возможность up cast
		assert(dynamic_cast<Component*>(component.get()) != nullptr);

		// хэш новой компоненты
		size_t hashCode{ typeid(TComponent).hash_code() };

		// если такая компонента уже есть, то это проблема с кодом
		assert(!components.contains(hashCode));

		// добавляем новую компоненту 
		components.emplace(hashCode, std::move(component));
	}
};