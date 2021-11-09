#pragma once
#include "Component.h" 
#include <vector>

class RRTexture; 

/// <summary>
/// ������ ������ ������� GameIO::DrawTexture � ��������� ��������
/// </summary>
/// <param name="object">- GameObject � ����������� DrawingCompontent</param>
/// <param name="size">- ������ �������� �� ������ � ��������</param>
void DrawObject(class GameObject* object, int size);

class DrawingComponent : public Component {
public:
	DrawingComponent();
	DrawingComponent(const RRTexture& texture);
	virtual ~DrawingComponent() {}

	void AddTexture(const RRTexture& texture);
	const RRTexture& GetTexture(int num) const;
	const RRTexture& GetTexture() const;

	void ChangeCurrentTexture(int num);
protected:
	int GetTexturesNum() const;
private:
	int currentTexture{};
	std::vector<const RRTexture*> textures;
};
 