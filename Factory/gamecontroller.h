#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QSize>

#include <vector>
#include <random>
#include <iostream>
#include <ctime>

class GameController
{
public:
    GameController();
    GameController(QSize size);

    void setSize(QSize size);
    bool setState(QSize pos, int state);

    int getState(QSize pos);
    bool isBomb(QSize pos);
    std::vector<std::vector<int>>* getMapOfGame();
    QSize getRightPos(QSize pos);
    int getCountBombs();
    bool isGone();

    bool validate(QSize pos);
    bool firstIsFree(int row, int col);
    void restart();
    void incrementBomb();
    void decrementBomb();
    void gameOver();
    bool endOfGame();
    int countBombs(QSize pos);
    void coverage(int row, int col, int state);
private:
    void init();
    void generate(int row = -1, int col = -1);
    void clear();
    void resize();
    void wideSearch(int row, int col, int depth = 0);
    void setSearchedTile(int row, int col, int depth);

    QSize _size;
    int _scale;
    int _bobms;
    bool _gone;
    int _count_tiles;

    std::vector<std::vector<int>> _map_of_game;
    std::vector<std::vector<bool>> _place_of_bomb;
    std::default_random_engine _generator;

    bool _first_is_free;

    enum Settings{
        BOMBS = 110,
        TILES = 25,
        CHANGE = 30,
        DEPTH = 4
    };
};

#endif // GAMECONTROLLER_H
