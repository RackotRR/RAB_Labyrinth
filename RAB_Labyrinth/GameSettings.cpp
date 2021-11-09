#include <assert.h>
#include "GameSettings.h"
 
void GameSettings::IncreaseCellSize(int value) {
	assert(value > 0);
	assert(value < 100);

	cellSize += value;
}
void GameSettings::DecreaseCellSize(int value) {
	assert(value > 0);
	assert(value < 100);

	cellSize -= value;

	if (cellSize < minCellSize) {
		cellSize = minCellSize;
	}
}

void GameSettings::SetCellSize(int cellSize) {
	assert(cellSize > minCellSize); 

	this->cellSize = cellSize;
}
int GameSettings::GetCellSize() const {
	return cellSize;
}  