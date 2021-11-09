#pragma once

class GameSettings {
public:
	void IncreaseCellSize(int value = 1);
	void DecreaseCellSize(int value = 1);

	void SetCellSize(int cellSize);
	int GetCellSize() const;
private:
	static constexpr int minCellSize{ 2 };
	int cellSize{};
};