#include "drawwin.h"

DrawWin::DrawWin(){}
DrawWin::~DrawWin(){}


//Vitruals
void DrawWin::draw(QPainter *p){
    p->fillRect(-1, -1, this->_size.width() + 1, this->_size.height() + 1, QColor(22, 22, 22, 120));
    QFont font("times", 30);
    p->setFont(font);
    p->setPen(QColor(Qt::white));
    p->drawText(this->_size.width()/2 - QFontMetrics(font).horizontalAdvance("You Win")/2, this->_size.height()/2, "You Win");
    p->setPen(QColor(Qt::black));
}
//~Virtuals

