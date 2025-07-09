#include <stdexcept>
#include "board.hpp"

Board::Board() {
	this->grid = std::vector<std::vector<CellState>>(height, std::vector<CellState>(width, CellState::Empty));
}

void Board::bounds(int row, int col) const {
	if (row < 0 || row >= height || col < 0 || col >= width) {
		throw std::invalid_argument("Row/Column out of bounds");
	}
}

CellState Board::getCell(int row, int col) const {
	bounds(row, col);
	return grid[row][col];
}

void Board::setCell(int row, int col, CellState state) {
	bounds(row, col);
	grid[row][col] = state;
}

bool Board::isRowFull(int row) const {
	bounds(row, 0);
	for (size_t i = 0; i < width; ++i) {
		if (grid[row][i] == CellState::Empty) {
			return false;
		}
	}
	return true;
}

void Board::clearRow(int row) {
	bounds(row, 0);

	for (size_t i = row; i > 0; --i) {
		grid[i] = grid[i - 1];
	}
	grid[0] = std::vector<CellState>(width, CellState::Empty);
}

void Board::clearFullRows() {
	int i = static_cast<int>(height) - 1;
	while (i >= 0) {
		if (isRowFull(i)) {
			clearRow(i);
		}
		else {
			i--;
		}
	}
}

size_t Board::getWidth() const {
	return width;
}

size_t Board::getHeight() const {
	return height;
}

void Board::reset() {
	for (size_t rows = 0; rows < height; ++rows) {
		for (size_t cols = 0; cols < width; ++cols) {
			grid[rows][cols] = CellState::Empty;
		}
	}
}