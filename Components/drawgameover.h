#ifndef DRAWGAMEOVER_H
#define DRAWGAMEOVER_H

//Custom classes
#include "Abstract/component.h"
//~Custom classes

class DrawGameOver : public Component
{
public:
    DrawGameOver();
    ~DrawGameOver();

    void draw(QPainter *painter) override;
};

#endif // DRAWGAMEOVER_H
