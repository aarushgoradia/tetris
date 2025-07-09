#include "game.hpp"

TetrominoType Game::randomType() {
	return static_cast<TetrominoType>(rand() % 7);
}

Game::Game() : current(randomType()), next(randomType()) {}

void Game::spawnTetromino() {

}

void Game::lockCurrent() {

}

bool Game::canPlace(const Tetromino& tetro) const {
	std::array<std::array<CellState, 4>, 4> matrix = tetro.getShapeMatrix();
	std::pair<int, int> pos = tetro.getPosition();
	int rowOffset = pos.first;
	int colOffset = pos.second;

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (matrix[row][col] == CellState::Filled) {
				int boardRow = rowOffset + row;
				int boardCol = colOffset + col;

				if (boardRow >= board.getHeight() || boardCol >= board.getWidth() || boardCol < 0) {
					return false;
				}
				else if (board.getCell(boardRow, boardCol) == CellState::Filled) {
					return false;
				}
			}
		}
	}
	return true;
}

void updateLevel() {

}

void Game::update(double deltaTime) {
	fallTimer += deltaTime;
	if (fallTimer >= fallInterval) {
		Tetromino moved = current;
		moved.move(1, 0);

		if (canPlace(moved)) {
			current.move(1, 0);
		}
		else {
			lockCurrent();
			spawnTetromino();

			if (!canPlace(current)) {
				gameOver = true;
				return;
			}
		}
		fallTimer = 0.0;
	}
}
