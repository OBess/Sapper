#include "drawfield.h"

DrawField::DrawField(){}
DrawField::~DrawField(){}


//Vitruals
void DrawField::draw(QPainter *p){
    if(this->_map_of_field == nullptr || this->_map_of_field->size() == 0)
        return;
    int scale = this->_size.width() / this->_map_of_field[0].size();
    for(int i{0}; i < (int)this->_map_of_field->size(); i++)
        for(int j{0}; j < (int)this->_map_of_field->at(i).size(); j++){
            switch (this->_map_of_field->at(i)[j]) {
            case 0:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            case -1:
                p->setBrush(QColor("#45a300"));
                p->drawRect(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            case -2:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                p->setBrush(Qt::red);
                p->drawEllipse(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            case -3:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale, i * scale , scale, scale);
                p->setBrush(Qt::black);
                p->setBrush(Qt::yellow);
                p->drawEllipse(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            case -4:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale, i * scale , scale, scale);
                p->setBrush(Qt::black);
                p->setBrush(QColor("#329da8"));
                p->drawEllipse(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            case -5:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                p->setBrush(QColor("#7e009e"));
                p->drawEllipse(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                break;
            default:
                p->setBrush(QColor("#114505"));
                p->drawRect(j * scale , i * scale , scale, scale);
                p->setBrush(Qt::black);
                p->setPen(QColor("#42aaf5"));
                p->setFont(QFont("sans_serif", 14));
                p->drawText(j * scale + scale/4, i * scale + scale - scale/4, std::to_string(this->_map_of_field->at(i)[j]).c_str());
                p->setPen(QPen(Qt::black, 1, Qt::SolidLine));
            }
        }
}
//~Virtuals
