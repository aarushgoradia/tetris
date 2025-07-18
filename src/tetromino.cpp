#include <stdexcept>
#include "tetromino.hpp"

namespace {
	using Matrix = std::array<std::array<CellState, 4>, 4>;

	constexpr CellState F = CellState::Filled;
	constexpr CellState E = CellState::Empty;

	const std::array<Matrix, 4> I_SHAPE = { {
		{{ {E, E, E, E},
		   {F, F, F, F},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, E, F, E},
		   {E, E, F, E},
		   {E, E, F, E},
		   {E, E, F, E} }},
		{{ {E, E, E, E},
		   {E, E, E, E},
		   {F, F, F, F},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {E, F, E, E},
		   {E, F, E, E},
		   {E, F, E, E} }}
	} };

	const std::array<Matrix, 4> O_SHAPE = { {
		{{ {E, F, F, E},
		   {E, F, F, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		   // O-shape is rotationally symmetric
		   {{ {E, F, F, E},
			  {E, F, F, E},
			  {E, E, E, E},
			  {E, E, E, E} }},
		   {{ {E, F, F, E},
			  {E, F, F, E},
			  {E, E, E, E},
			  {E, E, E, E} }},
		   {{ {E, F, F, E},
			  {E, F, F, E},
			  {E, E, E, E},
			  {E, E, E, E} }}
	   } };

	const std::array<Matrix, 4> T_SHAPE = { {
		{{ {E, F, E, E},
		   {F, F, F, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {E, F, F, E},
		   {E, F, E, E},
		   {E, E, E, E} }},
		{{ {E, E, E, E},
		   {F, F, F, E},
		   {E, F, E, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {F, F, E, E},
		   {E, F, E, E},
		   {E, E, E, E} }}
	} };

	const std::array<Matrix, 4> S_SHAPE = { {
		{{ {E, F, F, E},
		   {F, F, E, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {E, F, F, E},
		   {E, E, F, E},
		   {E, E, E, E} }},
		{{ {E, E, E, E},
		   {E, F, F, E},
		   {F, F, E, E},
		   {E, E, E, E} }},
		{{ {F, E, E, E},
		   {F, F, E, E},
		   {E, F, E, E},
		   {E, E, E, E} }}
	} };

	const std::array<Matrix, 4> Z_SHAPE = { {
		{{ {F, F, E, E},
		   {E, F, F, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, E, F, E},
		   {E, F, F, E},
		   {E, F, E, E},
		   {E, E, E, E} }},
		{{ {E, E, E, E},
		   {F, F, E, E},
		   {E, F, F, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {F, F, E, E},
		   {F, E, E, E},
		   {E, E, E, E} }}
	} };

	const std::array<Matrix, 4> J_SHAPE = { {
		{{ {F, E, E, E},
		   {F, F, F, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, F, F, E},
		   {E, F, E, E},
		   {E, F, E, E},
		   {E, E, E, E} }},
		{{ {E, E, E, E},
		   {F, F, F, E},
		   {E, E, F, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {E, F, E, E},
		   {F, F, E, E},
		   {E, E, E, E} }}
	} };

	const std::array<Matrix, 4> L_SHAPE = { {
		{{ {E, E, F, E},
		   {F, F, F, E},
		   {E, E, E, E},
		   {E, E, E, E} }},
		{{ {E, F, E, E},
		   {E, F, E, E},
		   {E, F, F, E},
		   {E, E, E, E} }},
		{{ {E, E, E, E},
		   {F, F, F, E},
		   {F, E, E, E},
		   {E, E, E, E} }},
		{{ {F, F, E, E},
		   {E, F, E, E},
		   {E, F, E, E},
		   {E, E, E, E} }}
	} };
}

Tetromino::Tetromino(TetrominoType shape) {
	this->shape = shape;
	rotation = 0;
	position = { 0, 3 };
}

void Tetromino::rotateCW() {
	rotation = (rotation + 1) % 4;
}
void Tetromino::rotateCCW() {
	rotation = (rotation + 3) % 4;
}

bool Tetromino::isFilledAt(int row, int col) const {
	return (getShapeMatrix()[row][col] == CellState::Filled);
}
std::array<std::array<CellState, 4>, 4> Tetromino::getShapeMatrix() const {
	switch (shape) {
	case TetrominoType::I: return I_SHAPE[rotation];
	case TetrominoType::O: return O_SHAPE[rotation];
	case TetrominoType::T: return T_SHAPE[rotation];
	case TetrominoType::S: return S_SHAPE[rotation];
	case TetrominoType::Z: return Z_SHAPE[rotation];
	case TetrominoType::J: return J_SHAPE[rotation];
	case TetrominoType::L: return L_SHAPE[rotation];
	}
	throw std::runtime_error("Invalid tetromino type.");
}
std::pair<int, int> Tetromino::getPosition() const {
	return position;
}
void Tetromino::setPosition(int row, int col) {
	position = { row, col };
}

void Tetromino::move(int dx, int dy) {
	position.first += dy;
	position.second += dx;
}
void Tetromino::reset(TetrominoType newShape) {
	shape = newShape;
	rotation = 0;
	position = { 0, 3 };
}