#ifndef SMARTCALC1_CONTROLLER_H
#define SMARTCALC1_CONTROLLER_H

#include <QObject>
#include "../model/model.h"
#include "../view/view.h"

namespace s21 {

class Controller : public QObject {
    Q_OBJECT

public:
    explicit Controller(View *View, Model *Model);

private:
    Model   *Model_;
    View    *View_;
};

}  // namespace s21

#endif //SMARTCALC1_CONTROLLER_H
