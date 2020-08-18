#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _offset{25}
{
    ui->setupUi(this);
    this->_panel = new Panel(this->_offset, this);
    this->_game_controller = new GameController({this->size().width(), this->size().height() - this->_offset});

    this->_panel->setGameController(this->_game_controller);
}

MainWindow::~MainWindow()
{
    delete this->_panel;
    delete this->_game_controller;
    delete ui;
}

