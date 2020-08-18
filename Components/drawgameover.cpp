#include "drawgameover.h"

DrawGameOver::DrawGameOver(){}
DrawGameOver::~DrawGameOver(){}

//Vitruals
void DrawGameOver::draw(QPainter *p){
    p->fillRect(-1, -1, this->_size.width() + 1, this->_size.height() + 1, QColor(22, 22, 22, 120));
    QFont font("times", 30);
    p->setFont(font);
    p->setPen(QColor(Qt::white));
    p->drawText(this->_size.width()/2 - QFontMetrics(font).horizontalAdvance("You Lost")/2, this->_size.height()/2, "You Lost");
    p->setPen(QColor(Qt::black));
}
//~Virtuals

