#ifndef DRAWWIN_H
#define DRAWWIN_H

//Custom classes
#include "Abstract/component.h"
//~Custom classes

class DrawWin : public Component
{
public:
    DrawWin();
    ~DrawWin();

    void draw(QPainter *painter) override;
};

#endif // DRAWWIN_H
