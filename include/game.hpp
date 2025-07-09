#pragma once

#include "board.hpp"
#include "tetromino.hpp"

enum class InputAction {
    MoveLeft,
    MoveRight,
    SoftDrop,
    HardDrop,
    RotateCW,
    RotateCCW,
    None
};

class Game {
private:
    Board board;
    Tetromino current;
    Tetromino next;

    bool gameOver = false;

    double fallTimer = 0.0;
    double fallInterval = 0.5;

    int score = 0;
    int level = 1;
    int linesCleared = 0;

    TetrominoType randomType();
    void spawnTetromino();
    void lockCurrent();
    bool canPlace(const Tetromino&) const;
    void updateLevel();

public:
    Game();

    void update(double deltaTime); // called every frame
    void handleInput(InputAction action);

    const Board& getBoard() const;
    const Tetromino& getCurrent() const;
    bool isGameOver() const;
    int getScore() const;
    int getLevel() const;
};
