#ifndef SMARTCALC1_CONTROLLER_H
#define SMARTCALC1_CONTROLLER_H

#include <QObject>
#include "../model/model.h"
#include "../view/view.h"

namespace s21 {

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(View *view, Model *model);

private:
    Model   *model_;
    View    *view_;
};

}  // namespace s21

#endif //SMARTCALC1_CONTROLLER_H
