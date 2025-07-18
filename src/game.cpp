#include <iostream>
#include <cstdlib>
#include "game.hpp"


TetrominoType Game::randomType() {
	return static_cast<TetrominoType>(rand() % 7);
}

Game::Game() : current(randomType()), next(randomType()) {}

void Game::spawnTetromino() {
	current = next;
	next = Tetromino(randomType());
	// Reset the position of the new tetromino
	current.setPosition(0, board.getWidth() / 2 - 2); // Start at the top center of the board
	if (!canPlace(current)) {
		gameOver = true; // Cannot place the new tetromino, game over
	}
}

void Game::lockCurrent() {
	auto matrix = current.getShapeMatrix();
	auto [rowOffset, colOffset] = current.getPosition();

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			if (matrix[row][col] == CellState::Filled) {
				int boardRow = rowOffset + row;
				int boardCol = colOffset + col;
				if (boardRow >= 0 && boardRow < board.getHeight() && boardCol >= 0 && boardCol < board.getWidth()) {
					board.setCell(boardRow, boardCol, CellState::Filled);
				}
			}
		}
	}

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

void Game::updateLevel() {
	level = linesCleared / 10 + 1;
	fallInterval = std::max(0.1, 0.5 - (level - 1) * 0.05);
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

void Game::handleInput(InputAction action) {
	if (gameOver) return;
	Tetromino moved = current;
	switch (action) {
	case InputAction::MoveLeft:
		moved.move(0, -1);
		break;
	case InputAction::MoveRight:
		moved.move(0, 1);
		break;
	case InputAction::SoftDrop:
		moved.move(1, 0);
		break;
	case InputAction::HardDrop:
		while (canPlace(moved)) {
			current = moved;
			moved.move(1, 0);
			fallTimer = 0.0; // Reset fall timer on hard drop
		}
		lockCurrent();
		spawnTetromino();
		return; // Skip the rest of the input handling
	case InputAction::RotateCW:
		moved.rotateCW();
		break;
	case InputAction::RotateCCW:
		moved.rotateCCW();
		break;
	default:
		return; // No action
	}
	if (canPlace(moved)) {
		current = moved;
	}
}

const Board& Game::getBoard() const {
	return board;
}

const Tetromino& Game::getCurrent() const {
	return current;
}

bool Game::isGameOver() const {
	return gameOver;
}

int Game::getScore() const {
	return score;
}

int Game::getLevel() const {
	return level;
}