#include "DrawingComponent.h" 
#include <assert.h>
#include "RRTexture.h"
#include "GameObject.h"
#include "RRGameIO.h"

DrawingComponent::DrawingComponent() : currentTexture{}
{ 
}

DrawingComponent::DrawingComponent(const RRTexture& texture) : currentTexture{}
{
	AddTexture(texture);
}

void DrawingComponent::AddTexture(const RRTexture& texture) {
	textures.push_back(&texture);
}

const RRTexture& DrawingComponent::GetTexture(int num) const {
	assert(num < textures.size() && num >= 0);
	return *textures[num];
}

const RRTexture& DrawingComponent::GetTexture() const {
	assert(currentTexture < textures.size() && currentTexture >= 0);
	return *textures[currentTexture];
}

void DrawingComponent::ChangeCurrentTexture(int num) {
	currentTexture = num;
}

int DrawingComponent::GetTexturesNum() const {
	return static_cast<int>(textures.size());
}
 
void DrawObject(GameObject* object, int size) {
	// выполняем, если есть компонента DrawingComponent
	if (auto hasDrawingComponent{ object->GetComponent<DrawingComponent>() }; hasDrawingComponent.has_value()) {

		auto& gameIO{ RRGameIO::Instance() };
		auto* drawingComponent{ hasDrawingComponent.value() };
		Vector2 position{ object->GetPosition() };

		// нарисовать текстуру по указанным координатам с указанными размерами
		gameIO.DrawTexture(
			Rectangle{
				position.X * size,
				position.Y * size,
				size,
				size
			},
			drawingComponent->GetTexture()
		);
	}
}

