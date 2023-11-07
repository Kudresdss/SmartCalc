#include "qlabelhorizontal.h"

namespace s21 {

QLabelHorizontal::QLabelHorizontal(QWidget *parent) : QLabel(parent) {}

void QLabelHorizontal::paintEvent(QPaintEvent *paint_event) {
    QPainter painter = QPainter(this);
    painter.save();
    painter.rotate(10);
    painter.drawText(paint_event->rect(), this->text());
    painter.restore();
}

}  // namespace s21
