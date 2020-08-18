#ifndef COMPONENT_H
#define COMPONENT_H

//Casses of qt
#include <QWidget>
#include <QPainter>
#include <QSize>
//~Casses of qt

//Classes c++
#include <vector>
//~Classes c++


class Component
{
public:
    Component() : _drawing{false} {}
    virtual ~Component() {};
    virtual void draw(QPainter* painter) = 0;

    void setDrawing(bool drawing){this->_drawing = drawing;}
    void setSize(QSize size){this->_size = size;}
    void setSize(int w, int h){this->_size = {w, h};}
    void setMapOfFieild(std::vector<std::vector<int>>* map_of_field){this->_map_of_field = map_of_field;}

    bool getDrawing(){return this->_drawing;}
protected:
    bool _drawing;
    QSize _size;
    std::vector<std::vector<int>>* _map_of_field;
};

#endif // COMPONENT_H
