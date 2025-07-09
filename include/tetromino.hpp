#pragma once

#include <array>
#include "board.hpp"

enum class TetrominoType {
	I, O, T, J, L, S, Z
};

class Tetromino {
private:
	TetrominoType shape;
	int rotation;
	std::pair<int, int> position;

public:
	Tetromino();

	void rotateCW();
	void rotateCCW();

	bool isFilledAt(int row, int col);
	std::array<std::array<CellState, 4>, 4> getShapeMatrix() const;
	std::pair<int, int> getPosition() const;

	void move(int dy, int dx);
	void reset(TetrominoType newShape);

};