#include "gamecontroller.h"

GameController::GameController() : _size{800, 600}{
    this->init();
}
GameController::GameController(QSize size) : _size{size}{
    this->init();
}


//Init
void GameController::init(){
    this->_gone = true;
    this->_bobms = BOMBS;
    this->_count_tiles = TILES;
    this->resize();
    this->restart();
}
//~Init


//Setters
void GameController::setSize(QSize size){
    this->_size = size;
}
bool GameController::setState(QSize pos, int state){
    if(!this->_gone) return false;
    this->_map_of_game.at(pos.width())[pos.height()] = state;
    return true;
}
//~Setters


//Getters
int GameController::getState(QSize pos){
    return this->_map_of_game[pos.width()][pos.height()];
}
bool GameController::isBomb(QSize pos){
    return this->_place_of_bomb[pos.width()][pos.height()];
}
std::vector<std::vector<int>>* GameController::getMapOfGame(){
    return &this->_map_of_game;
}
QSize GameController::getRightPos(QSize pos){
    return {(int)(pos.height()/this->_scale), (int)(pos.width()/this->_scale)};
}
int GameController::getCountBombs(){
    return this->_bobms;
}
bool GameController::isGone(){
    return this->_gone;
}
//~Getters


//Logic
bool GameController::validate(QSize pos){
    return pos.width() >= (int)this->_map_of_game.size() || pos.height() >= (int)this->_map_of_game[0].size() || !this->_gone;
}
bool GameController::firstIsFree(int row, int col){
    if(!this->_first_is_free){
        this->generate(row, col);
        this->_first_is_free = true;
        return true;
    }
    return false;
}
void GameController::restart(){
    this->_gone = true;
    this->_bobms = BOMBS;
    this->_first_is_free = false;
    this->clear();
}
void GameController::incrementBomb(){
    if(!this->_gone) return;
    this->_bobms++;
}
void GameController::decrementBomb(){
    if(!this->_gone) return;
    this->_bobms--;
}
void GameController::gameOver(){
    this->_gone = false;
    for(int i{0}; i < (int)this->_map_of_game.size(); i++)
        for(int j{0}; j < (int)this->_map_of_game[i].size(); j++){
            if(this->_place_of_bomb[i][j]){
                if(this->_map_of_game[i][j] == -3)
                    this->_map_of_game[i][j] = -4;
                else if(this->_map_of_game[i][j] != -5)
                    this->_map_of_game[i][j] = -2;
            }
        }
}
void GameController::clear(){
    for(int i = 0; i < this->_count_tiles; i++){
        for(int j = 0; j < this->_count_tiles; j++){
            this->_map_of_game[i][j] = -1;
        }
    }

    for(int i = 0; i < this->_count_tiles; i++){
        for(int j = 0; j < this->_count_tiles; j++){
            this->_place_of_bomb[i][j] = false;
        }
    }
}
void GameController::generate(int row_, int col_){
    int row, col;
    int remaining_bombs = this->_bobms;
    std::uniform_int_distribution<int> distribution(0, this->_count_tiles - 1);
    do{
        row = distribution(this->_generator);
        col = distribution(this->_generator);

        if(!this->_place_of_bomb[row][col] && row != row_ && col != col_){
            this->_place_of_bomb[row][col] = true;
            --remaining_bombs;
        }
    }while(remaining_bombs > 0);
}
void GameController::resize(){
    this->_map_of_game.resize(this->_count_tiles);
    for(int i = 0; i < this->_count_tiles; i++){
        this->_map_of_game[i].resize(this->_count_tiles);
    }
    this->_place_of_bomb.resize(this->_count_tiles);
    for(int i = 0; i < this->_count_tiles; i++){
        this->_place_of_bomb[i].resize(this->_count_tiles);
    }
    this->_scale = this->_size.width() / this->_map_of_game[0].size();
}
bool GameController::endOfGame(){
    if(this->_bobms != 0)
        return false;
    for(size_t i = 0; i < this->_map_of_game.size(); i++)
        for(size_t j = 0; j < this->_map_of_game[i].size(); j++)
            if(this->_map_of_game[i][j] == -1)
                return false;
    this->_gone = false;
    return true;
}
int GameController::countBombs(QSize pos){
    int bombs = 0;
    if(pos.width() >= (int)this->_map_of_game.size() || pos.height() >= (int)this->_map_of_game[0].size())
        return bombs;
    if(pos.width() - 1 >= 0 && pos.height() - 1 >= 0 && this->_place_of_bomb[pos.width() - 1][pos.height() - 1])        //left-top
        bombs++;
    if(pos.height() - 1 >= 0 && this->_place_of_bomb[pos.width()][pos.height() - 1])                                    //top
        bombs++;
    if(pos.width() + 1 < (int)this->_place_of_bomb[0].size() && pos.height() - 1 >= 0 && this->_place_of_bomb[pos.width() + 1][pos.height() - 1])//right-top
        bombs++;
    if(pos.width() - 1 >= 0 && this->_place_of_bomb[pos.width() - 1][pos.height()])        //left
        bombs++;
    if(pos.width() + 1 < (int)this->_place_of_bomb[0].size() && this->_place_of_bomb[pos.width() + 1][pos.height()])    //right
        bombs++;
    if(pos.width() - 1 >= 0 && pos.height() + 1 < (int)this->_place_of_bomb.size() && this->_place_of_bomb[pos.width() - 1][pos.height() + 1])//left-bottom
        bombs++;
    if(pos.height() + 1 < (int)this->_place_of_bomb.size() && this->_place_of_bomb[pos.width()][pos.height() + 1])      //bottom
        bombs++;
    if(pos.width() + 1 < (int)this->_place_of_bomb[0].size() && pos.height() + 1 < (int)this->_place_of_bomb.size() && this->_place_of_bomb[pos.width() + 1][pos.height() + 1])//right-botom
        bombs++;
    return bombs;
}
void GameController::coverage(int row, int col, int state){
    std::uniform_int_distribution<int> distribution(1, 100);
    this->_map_of_game.at(row)[col] = state;
    if(distribution(this->_generator) < CHANGE)
        this->wideSearch(row, col, DEPTH);
}
void GameController::wideSearch(int row, int col, int depth){
    if(depth <= 0) return;

    if(row - 1 >= 0 && col - 1 >= 0 && !this->_place_of_bomb[row - 1][col - 1]){                                                                //left-top
        this->setSearchedTile(row - 1, col - 1, depth);
    }
    if(col - 1 >= 0 && !this->_place_of_bomb[row][col - 1]){                                                                                    //top
        this->setSearchedTile(row, col - 1, depth);
    }
    if(row + 1 < (int)this->_place_of_bomb[0].size() && col - 1 >= 0 && !this->_place_of_bomb[row + 1][col - 1]){                               //right-top
        this->setSearchedTile(row + 1, col - 1, depth);
    }
    if(row - 1 >= 0 && !this->_place_of_bomb[row - 1][col]){                                                                                    //left
        this->setSearchedTile(row - 1, col, depth);
    }
    if(row + 1 < (int)this->_place_of_bomb[0].size() && !this->_place_of_bomb[row + 1][col]){                                                   //right
        this->setSearchedTile(row + 1, col, depth);
    }
    if(row - 1 >= 0 && col + 1 < (int)this->_place_of_bomb.size() && !this->_place_of_bomb[row - 1][col + 1]){                                  //left-bottom
        this->setSearchedTile(row - 1, col + 1, depth);
    }
    if(col + 1 < (int)this->_place_of_bomb.size() && !this->_place_of_bomb[row - 1][col + 1]){                                                  //bottom
        this->setSearchedTile(row, col + 1, depth);
    }
    if(row + 1 < (int)this->_place_of_bomb[0].size() && col + 1 < (int)this->_place_of_bomb.size() && !this->_place_of_bomb[row + 1][col + 1]){ //right-botom
        this->setSearchedTile(row + 1, col + 1, depth);
    }
}
void GameController::setSearchedTile(int row, int col, int depth){
    if(this->_map_of_game[row][col] != -3){
        if(this->countBombs({row, col}) == 0){
            this->_map_of_game[row][col] = 0;
            this->wideSearch(row, col, --depth);
        }
        else
            this->_map_of_game[row][col] = this->countBombs({row, col});
    }
}
//~Logic
