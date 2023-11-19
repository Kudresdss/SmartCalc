#include "line_edit_click_filter.h"

namespace s21 {

LineEditClickFilter::LineEditClickFilter() : QObject() {}

bool LineEditClickFilter::eventFilter(QObject *obj, QEvent *event) {
    QString sender_name = obj->objectName();

    if (event->type() == QEvent::FocusIn) {
        if (sender_name == "lineEdit_input") {
            emit SignalLineEdit_Input();
        }
        else emit SignalLineEdit_X();
    }
    else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}

}  // namespace s21
