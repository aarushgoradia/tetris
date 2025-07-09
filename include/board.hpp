#pragma once

#include <vector>
#include <array>

enum class CellState {
	Empty,
	Filled
};



class Board {
private:
	std::vector<std::vector<CellState>> grid;
	static constexpr size_t width{10};
	static constexpr size_t height{20};
	void bounds(int row, int col) const;

public:
	Board();

	CellState getCell(int row, int col) const;
	void setCell(int row, int col, CellState state);

	bool isRowFull(int row) const;
	void clearRow(int row);
	void clearFullRows();

	size_t getWidth() const;
	size_t getHeight() const;

	void reset();
};