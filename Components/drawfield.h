#ifndef DRAWFIELD_H
#define DRAWFIELD_H

//Custom classes
#include "Abstract/component.h"
//~Custom classes

#include <vector>

class DrawField : public Component
{
public:
    DrawField();
    ~DrawField();

    void draw(QPainter *painter) override;

private:
    short _scale = 20;
};

#endif // DRAWFIELD_H
