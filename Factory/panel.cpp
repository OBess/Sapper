#include "panel.h"

Panel::Panel(QWidget *parent) : QWidget(parent), _offset{0}
{
    this->_parent = parent;
    this->setSizeWidget(parent->size().width(), parent->size().height());
    this->init();
    this->connection();

    this->setMouseTracking(true);
}
Panel::Panel(short offset, QWidget *parent) : QWidget(parent), _offset{offset}
{
    this->_parent = parent;
    this->setSizeWidget(parent->size().width(), parent->size().height());
    this->init();
    this->connection();

    this->setMouseTracking(true);
}
Panel::~Panel(){
    //Clear memory from components
    for (Component* component: this->_components)
        delete component;
    this->_components.clear();

    delete this->_restart_btn;
    delete this->_count_of_bombs_lbl;
}


//Init
void Panel::init(){
    //Initial components
    this->_components.push_back(new DrawField);
    this->_components[0]->setSize(this->width(), this->height() - this->_offset);
    this->_components[0]->setDrawing(true);
    this->_components.push_back(new DrawGameOver);
    this->_components[1]->setSize(this->width(), this->height() - this->_offset * 2);
    this->_components.push_back(new DrawWin);
    this->_components[2]->setSize(this->width(), this->height() - this->_offset * 2);

    //Initial push button
    this->_restart_btn = new QPushButton(this);
    this->_restart_btn->setGeometry(0, this->height() - this->_offset * 2, 100, 30);
    this->_restart_btn->setText("Restart");

    //Initial bomb`s label
    this->_count_of_bombs_lbl = new QLabel(this);
    this->_count_of_bombs_lbl->setGeometry(this->width() - 30, this->height() - this->_offset * 2, 100, 40);
    this->_count_of_bombs_lbl->setFont(QFont("times", 14));
    this->_count_of_bombs_lbl->setStyleSheet("QLabel { color : white; }");
    this->_count_of_bombs_lbl->setText(std::to_string(30).c_str());
}
void Panel::connection(){
    connect(this->_restart_btn, SIGNAL(clicked()), this, SLOT(restart()));
}
//~Init


//Setters
void Panel::setSizeWidget(float w, float h){
    this->_size_widget.setWidth(w);
    this->_size_widget.setHeight(h);
    this->resize(w, h);
}
void Panel::setSizeWidget(QSize r){
    this->setSizeWidget(r.width(), r.height());
}
void Panel::setGameController(GameController *gameController){
    this->_game_contorller = gameController;
    this->_components[0]->setMapOfFieild(this->_game_contorller->getMapOfGame());
}
//~Setters


//Slots
void Panel::restart(){
    this->_game_contorller->restart();
    this->_components[1]->setDrawing(false);
    this->_components[2]->setDrawing(false);
    this->update();
}
//~Slots


//Events
void Panel::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    if(this->_start_work_counter)
        this->_count_of_bombs_lbl->setText(std::to_string(this->_game_contorller->getCountBombs()).c_str());
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::black));                        //Background
    painter.drawRect(-1, -1, this->width(), this->height());

    for(auto component: this->_components){
        if(component->getDrawing()){
            component->draw(&painter);
        }
    }

    this->_start_work_counter = true;
}
void Panel::mousePressEvent(QMouseEvent *event){
    QSize rightPos = this->_game_contorller->getRightPos({event->pos().x(), event->pos().y()});
    qDebug() << rightPos.width() << " - " << rightPos.height();
    if(this->_game_contorller->validate(rightPos))
        return;
    if(event->button() == Qt::LeftButton){
        if(this->_game_contorller->getState(rightPos) == -1){
            if(this->_game_contorller->isBomb(rightPos)){
                this->_components[1]->setDrawing(true);
                this->_game_contorller->setState(rightPos, -5);
                this->_game_contorller->gameOver();
            }else{
                this->_game_contorller->firstIsFree(rightPos.width(), rightPos.height());
                this->_game_contorller->coverage(rightPos.width(), rightPos.height(), this->_game_contorller->countBombs(rightPos));
            }
            this->update();
        }
    }
    else if(event->button() == Qt::RightButton){
        if(this->_game_contorller->getState(rightPos) == -1){
            if(this->_game_contorller->setState(rightPos, -3))
                this->_game_contorller->decrementBomb();
            this->update();
        }else if(this->_game_contorller->getState(rightPos) == -3){
            if(this->_game_contorller->setState(rightPos, -1))
                this->_game_contorller->incrementBomb();
            this->update();
        }
    }
    if(this->_game_contorller->endOfGame()){
        this->_components[2]->setDrawing(true);
        this->update();
    }
}
void Panel::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R)
        this->restart();
}
//~Events


//Designer
void Panel::disableAllComponent(){
    for(auto it: this->_components)
        it->setDrawing(false);
}
void Panel::enableAllComponent(){
    for(auto it: this->_components)
        it->setDrawing(true);
}
//~Designer
