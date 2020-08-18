#ifndef PANEL_H
#define PANEL_H

//Casses of qt
#include <QWidget>

#include <QSize>
#include <QPainter>
#include <QPointF>

#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QDebug>
//~Casses of qt

//Classes c++
#include <vector>
//~Classes c++

//Custom classes
#include "Abstract/component.h"
#include "Factory/gamecontroller.h"

    //Components
#include "Components/drawfield.h"
#include "Components/drawgameover.h"
#include "Components/drawwin.h"
    //~Components
//~Custom classes

class Panel : public QWidget
{
    Q_OBJECT
public:
    explicit Panel(QWidget *parent = nullptr);
    explicit Panel(short offset, QWidget *parent = nullptr);
    ~Panel();

    void setSizeWidget(float w, float h);
    void setSizeWidget(QSize r);
    void setGameController(GameController* gameController);

    void disableAllComponent();
    void enableAllComponent();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void restart();

private:
    void init();                        //setting initial program initialization
    void connection();

    std::vector<Component*> _components;
    GameController* _game_contorller;
    QPushButton* _restart_btn;
    QLabel* _count_of_bombs_lbl;

    QWidget* _parent;                    //ponter to parent widget
    QSize _size_widget;                  //size of panel

    const short _offset;
    bool _start_work_counter;
};

#endif // PANEL_H
